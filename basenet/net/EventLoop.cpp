#include "EventLoop.h"
#include <poll.h>
#include <iostream>

using namespace Walle;

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	: mLooping(false),
	mThreadID(CurrentThread::tid())
{
    std::cout << "EventLoop create " << this << " in thread" << mThreadID << std::endl;
	if (t_loopInThisThread)
	{
	    std::cout << "Another EventLoop" << t_loopInThisThread
			  << "exist in this thread" << mThreadID << std::endl;
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

	std::cout << "EventLoop" << "stop looping" << std::endl;
	mLooping = false;
}

void EventLoop::abortNotInLoopThread()
{
    std::cout << "EventLoop::abortNotInLoopThread - EventLoop" << this
		  << "was created in threadID " << mThreadID
		  << ", current threadID is " << CurrentThread::tid() 
		  << std::endl;
}
