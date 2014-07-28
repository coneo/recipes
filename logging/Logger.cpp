#include "Logger.h"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

Logger gLogger;

Logger::Logger()
{
}

Logger::~Logger()
{
}

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

const char* Logger::getLevelStr(LogLevel l)
{
    switch (l)
    {
        case LL_DEBUG:
            return "DEBUG";
        case LL_TRACE:
            return "TRACE";
        case LL_NOTICE:
            return "NOTICE";
        case LL_WARN:
            return "WARN";
        case LL_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

void Logger::formatTime()
{
};
