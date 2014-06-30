#ifndef WALLE_BASE_MUTEX_H
#define WALLE_BASE_MUTEX_H

#include <pthread.h>

#include <boost/noncopyable.hpp>

class MutexLock : boost::noncopyable
{
public:
	MutexLock()
	{
		pthread_mutex_init(&mMutex, NULL);
	}

	~MutexLock()
	{
		pthread_mutex_destroy(&mMutex);
	}

	void lock()
	{
		pthread_mutex_lock(&mMutex);
	}

	void unlock()
	{
		pthread_mutex_unlock(&mMutex);
	}

	pthread_mutex_t *getPthreadMutex() //仅供Condition调用
	{
		return &mMutex;
	}

private:

	pthread_mutex_t mMutex;
};

class MutexLockGuard : boost::noncopyable
{
public:
	MutexLockGuard(MutexLock &mutex) : mMutex(mutex)
	{
		mMutex.lock();
	}

	~MutexLockGuard()
	{
		mMutex.unlock();
	}

private:

	MutexLock &mMutex;
};

#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name")

#endif
