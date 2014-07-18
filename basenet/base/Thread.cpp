#include "Thread.h"
#include <stdio.h>

void* startThread(void*data);

Thread::Thread(const ThreadFunc& func, std::string name)
    : mPthreadID(0),
      mStarted(false),
      mJoined(false),
      mFunc(func),
      mName(name)
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    assert(!mStarted);
    mStarted = true;

    int flag = pthread_create(&mPthreadID,NULL,&startThread,this);
    if (flag)
    {
	mStarted = false;
	printf("error : pthread_create error code:%d",flag);
	abort();
    }
}

void Thread::join()
{
    assert(mStarted);
    assert(!mJoined);
    mJoined = true;
    pthread_join(mPthreadID,NULL);
}

void Thread::runThread()
{
    mFunc();
}

void* startThread(void *data)
{
    Thread* thread = static_cast<Thread*>(data);
    thread->runThread();
    return NULL;
}
