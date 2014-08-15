#include "logger.h"
#include "backend_logger.h"
#include <unistd.h>
#include <iostream>
#include <functional>
#include <chrono>
#include <memory>

using namespace water;

int32_t g_total;
FILE* g_file;
std::shared_ptr<BackendLogger> bkLogger;
struct stFoo
{
    int a{2};
    std::string s{"hello"};
};

LogStream& operator << (LogStream& ss, stFoo& foo)
{
    ss << "a=" << foo.a << " " << "s=" << foo.s;
    return ss;
}

void dumpfunc(const char* msg, uint32_t len)
{
    g_total += len;
    if (g_file)
    {
        fwrite(msg, 1, len, g_file);
    }
    else if(bkLogger)
    {
        bkLogger->append(msg, len);
    }
}

void bench()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    const int batch = 1000*1000;
    g_total = 0;

    for (int i = 0; i < batch; ++i)
    {
        LOG_DEBUG("%s %s %d","Hello 0123456789","abcdefghijklmnopqrstuvwxyz", i);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = end - start;
    printf("%f seconds, %lu bytes, %.2f msg/s, %.2f MiB/s\n",
           seconds.count(), (long int)g_total, batch / seconds.count(), g_total / seconds.count() / 1024 / 1024);
}

int main()
{
    using namespace std::placeholders;
    bkLogger.reset(new BackendLogger);
    bkLogger->start();
    gLogger.setAppendCallback(std::bind(dumpfunc,_1, _2));
    LOG_DEBUG("int=%d,str=%s", 25,"hello");
    LOG_DEBUG("hello logging");

    int a{32};
    float f{33.3};
    std::string s{"logging"};
    stFoo foo;
    LOG_TRACE("int=%u,float=%f, %s", a, f, foo);

    bench();

    /*
    char buffer[64*1024];
    g_file = fopen("/dev/null", "w");
    setbuffer(g_file, buffer, sizeof buffer);
    bench();
    fclose(g_file);

    g_file = NULL;
    */

    sleep(8);
    bkLogger->stop();
}
