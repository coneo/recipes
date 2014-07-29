#pragma once

#include "EventLoop.h"

#include <vector>
#include <map>

namespace Walle
{

struct pollfd;

class Channel;

class Poller : boost::noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    ~Poller();

    Timestamp poll(int timeoutMs, ChannelList* activeChannels);

    void updateChannel(Channel* channel);

    void assertInLoopThread() { mLoop->assertInLoopThread();}

private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* mLoop;
    PollFdList mPollfds;
    ChannelMap mChannels;
};
}//namespace Walle
