#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"
#include <iostream>

using namespace walle;

__thread EventLoop* t_loopInThisThread = 0;
const int kPollTimeMs = 10000;

EventLoop::EventLoop()
	: mThreadID(CurrentThread::tid()),
      mPoller(new Poller(this))
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
    mQuit = false;
    
    while (!mQuit)
    {
        mActiveChannels.clear();
        mPoller->poll(kPollTimeMs, &mActiveChannels);
        for (auto it = mActiveChannels.begin(); it != mActiveChannels.end(); ++it)
        {
            (*it)->handleEvent();
        }
    }

	std::cout << "EventLoop" << "stop looping" << std::endl;
	mLooping = false;
}

void EventLoop::quit()
{
    mQuit = true;
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(channel && channel->ownerLoop() == this);
    assertInLoopThread();
    mPoller->updateChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
    std::cout << "EventLoop::abortNotInLoopThread - EventLoop" << this
		  << "was created in threadID " << mThreadID
		  << ", current threadID is " << CurrentThread::tid() 
		  << std::endl;
}
