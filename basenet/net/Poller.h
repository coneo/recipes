#pragma once

#include "EventLoop.h"

#include <chrono>
#include <vector>
#include <map>

struct pollfd;

namespace walle
{

typedef std::chrono::high_resolution_clock Clock;

class Channel;

class Poller : boost::noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    ~Poller();

    Clock::time_point poll(int timeoutMs, ChannelList* activeChannels);

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
}//namespace walle
