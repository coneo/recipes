#ifndef WALLE_NET_EVENTLOOP_H_
#define WALLE_NET_EVENTLOOP_H_

#include <boost/noncopyable.hpp>

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
#endif
