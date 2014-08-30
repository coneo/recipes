#pragma once

#include "../base/Thread.h"
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace walle
{
class Channel;
class Poller;

class EventLoop : boost::noncopyable
{
public:
	EventLoop();
	~EventLoop();

	void loop();

    void quit();

    void updateChannel(Channel* channel);

	void assertInLoopThread()
	{
		if (!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}

	bool isInLoopThread() const { return mThreadID == CurrentThread::tid();}

private:
	void abortNotInLoopThread();

private:
    typedef std::vector<Channel*> ChannelList;
	bool mLooping = false;
    bool mQuit = false;
	const pid_t mThreadID;
    boost::scoped_ptr<Poller> mPoller;
    ChannelList mActiveChannels;
};
} //namespace walle
