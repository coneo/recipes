#include "SyncLogger.h"
#include <iostream>
#include <functional>

int main()
{
    LOG_DEBUG("int=%d,str=%s", 25,"hello");
    LOG_DEBUG("hello logging");
    gLogger.setLogLevel(LogLevel::LL_WARN);
    LOG_DEBUG("int=%d,str=%s", 25,"hello");
    LOG_DEBUG("hello logging man");
    LOG_WARN("nice to meet %d",23);
    LOG_WARN("hello logging woman");
}
