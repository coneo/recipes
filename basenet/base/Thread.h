#pragma once

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <pthread.h>

namespace Walle
{
class Thread : boost::noncopyable
{
public:
    typedef boost::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc& func, std::string name = std::string());
    ~Thread();

    void start();
    void join();

    void runThread();
    bool started() { return mStarted; }
    const std::string& name() const { return mName; }

private:
    pthread_t mPthreadID;
    bool mStarted;
    bool mJoined;
    ThreadFunc mFunc;
    std::string mName;
};

namespace CurrentThread
{
    pid_t tid();
}
} //namespace Walle
