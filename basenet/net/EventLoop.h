#pragma once

#include "../base/Thread.h"
#include <boost/noncopyable.hpp>

namespace Walle
{
class Channel;

class EventLoop : boost::noncopyable
{
public:
	EventLoop();
	~EventLoop();

	void loop();

	void assertInLoopThread()
	{
		if (!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}

	bool isInLoopThread() const { return mThreadID == CurrentThread::tid(); }

private:

	void abortNotInLoopThread();

	bool mLooping;
	const pid_t mThreadID;
};
} //namespace Walle
