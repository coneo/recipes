#ifndef WALLE_BASE_CONDITION_H
#define WALLE_BASE_CONDITION_H

#include "Mutex.h"

#include <pthread.h>
#include <boost/noncopyable.hpp>

class Condition : boost::noncopyable
{
public:
	Condition(MutexLock &mutex) : mMutex(mutex)
	{
		pthread_cond_init(&mCond, NULL);
	}

	~Condition()
	{
		pthread_cond_destroy(&mCond);
	}

	void wait()
	{
		pthread_cond_wait(&mCond, mMutex.getPthreadMutex());
	}

	void notify()
	{
		pthread_cond_signal(&mCond);
	}

	void notifyAll()
	{
		pthread_cond_broadcast(&mCond);
	}

private:

	MutexLock &mMutex;
	pthread_cond_t mCond;
};
#endif
