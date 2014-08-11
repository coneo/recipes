#include "logger.h"
#include "backend_logger.h"
#include <unistd.h>
#include <iostream>
#include <functional>

using namespace water;

struct stFoo
{
    int a{2};
    std::string s{"hello"};
};

Logger::LogStream& operator << (Logger::LogStream& ss, stFoo& foo)
{
    ss << "a=" << foo.a << " " << "s=" << foo.s;
    return ss;
}

void printout(const char* msg, uint32_t len)
{
    printf("%s",msg);
}

void zerofunc()
{
}

int main()
{
    using namespace std::placeholders;
    BackendLogger bkLogger;
    gLogger.setAppendCallback(std::bind(&BackendLogger::append, &bkLogger,_1, _2));
    bkLogger.start();
    LOG_DEBUG("int=%d,str=%s", 25,"hello");
    LOG_DEBUG("hello logging");

    int a{32};
    float f{33.3};
    std::string s{"logging"};
    stFoo foo;
    LOG_TRACE("int=%u,float=%f, %s", a, f, foo);

    sleep(10);
    bkLogger.stop();
    //gLogger.printout();
}
