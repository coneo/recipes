#include "EventLoop.h"

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	: mLooping(false),
	mThreadID(CurrentThread::tid())
{
	LOG_TRACE << "EventLoop create" << this << "in thread" << mThreadID;
	if (t_loopInThisThread)
	{
		LOG_FATAL << "Another EventLoop" << t_loopInThisThread
			  << "exist in this thread" << mThreadID;
	}
	else
	{
		t_loopInThisThread = this;
	}
}

EventLoop::~EventLoop()
{
	assert(!mLooping);
	t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
	assert(!mLooping);
	assertInLoopThread();
	mLooping = true;

	::poll(NULL, 0, 5*1000);

	LOG_TRACE << "EventLoop" << this << "stop looping";
	mLooping = false;
}

void EventLoop::abortNotInLoopThread()
{
	LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop" << this
		  << "was created in threadID " << mThreadID
		  << ", current threadID is " << CurrentThread::tid();
}
