#include "logger.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

using namespace water;

Logger gLogger;

/*
void Logger::log(LogLevel level, char* format, ...)
{
    int MAX_BUF_SIZE = 4*1000*100;
    char buf[MAX_BUF_SIZE];
    bzero(buf, sizeof(buf));

    va_list args;
    va_start(args, format);
    vsnprintf(buf, MAX_BUF_SIZE, format, args);
    va_end(args);

    printf("%s",buf);
    //append cb
}*/

void defaultOutput(const char* msg, uint32_t len)
{
    fwrite(msg, 1, len, stdout);
}

using std::placeholders::_1;
using std::placeholders::_2;
Logger::Logger()
    : m_level(LogLevel::LL_DEBUG),
      m_appendcb(std::bind(&defaultOutput,_1,_2)) //FIXME:使用backend_logger的io
{
}

const char* Logger::getLevelStr(LogLevel l)
{
    switch (l)
    {
        case LogLevel::LL_DEBUG:
            return "DEBUG";
        case LogLevel::LL_TRACE:
            return "TRACE";
        case LogLevel::LL_WARN:
            return "WARN";
        case LogLevel::LL_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

void Logger::formatTime()
{
    time_t now;
    now = time(&now);
    struct tm vtm;
    localtime_r(&now, &vtm);
    m_stream << vtm.tm_year+1990 <<"-"<<vtm.tm_mon+1<<"-"<<vtm.tm_mday<<" "<<vtm.tm_hour<<":"<<vtm.tm_min<<":"<<vtm.tm_sec;
}

