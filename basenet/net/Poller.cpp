#include "Poller.h"
#include "Channel.h"
#include <poll.h>

using namespace walle;

Poller::Poller(EventLoop* loop):
  mLoop(loop)
{
}

Poller::~Poller()
{
}

Clock::time_point Poller::poll(int timeoutMs, ChannelList* activeChannels)
{
    int numEvents = ::poll(&*mPollfds.begin(), mPollfds.size(), timeoutMs);
    Clock::time_point now = Clock::now();
    if (numEvents > 0)
    {
        std::cout << numEvents << "events happened\n";
        fillActiveChannels(numEvents, activeChannels);
    }
    else if (numEvents == 0)
    {
        std::cout << "nothing happened\n";
    }
    else
    {
        std::cout << "error when" << __func__ << std::endl;
    }

    return now;
}

void Poller::updateChannel(Channel* channel)
{
    assertInLoopThread();
    std::cout << "fd= " << channel->fd() << "events=" << channel->events() << std::endl;
    if (channel->index() < 0)
    {
        assert(mChannels.find(channel->fd()) == mChannels.end());
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        mPollfds.push_back(pfd);
        int idx = static_cast<int>(mPollfds.size()) - 1;
        channel->setIndex(idx);
        mChannels[pfd.fd] = channel;
    }
    else
    {
        assert(mChannels.find(channel->fd()) != mChannels.end());
        assert(mChannels[channel->fd()] == channel);
        int idx = channel->index();
        assert(0 <= idx && idx < static_cast<int>(mPollfds.size()));
        struct pollfd& pfd = mPollfds[idx];
        assert(pfd.fd == channel->fd() || pfd.fd == -1);
        pfd.events = static_cast<short>(channel->events());
        pfd.revents = 0;
        if (channel->isNoneEvent())
        {
            pfd.fd = -1;
        }
    }
}

void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const
{
    for (PollFdList::const_iterator fdItr = mPollfds.begin();
         fdItr != mPollfds.end() && numEvents > 0; ++fdItr)
    {
        if (fdItr->revents > 0)
        {
            --numEvents;
            ChannelMap::const_iterator cItr = mChannels.find(fdItr->fd);
            assert(cItr != mChannels.end());
            Channel* channel = cItr->second;
            assert(channel->fd() == fdItr->fd);
            channel->setREvents(fdItr->revents);
            activeChannels->push_back(channel);
        }
    }
}
