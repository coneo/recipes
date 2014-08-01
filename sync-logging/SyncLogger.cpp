#include "SyncLogger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

__thread char SyncLogger::mBuffer[LOG_BUFFER_SIZE] = {0};
SyncLogger gLogger("./save.file");

SyncLogger::SyncLogger(const char* filename)
    :mLevel(LL_DEBUG),
     mWriter(filename)
{
}

void SyncLogger::log(LogLevel level, const char* file, int line, const char* fmt, ...)
{
    if (!compare(level)) return;

    char* bufp = mBuffer;
    size_t nSize = 0;

    //date
    nSize += appendDateTime(bufp, LOG_BUFFER_SIZE);
    bufp = mBuffer + nSize;

    //loglevel
    nSize += appendLogLevel(level, bufp, LOG_BUFFER_SIZE-nSize);
    bufp = mBuffer + nSize;

    //content
    va_list arg;
    va_start(arg, fmt);
    nSize += vsnprintf(bufp, LOG_BUFFER_SIZE-nSize, fmt, arg);
    bufp = mBuffer + nSize;
    va_end(arg);

    //file line
    nSize += appendFileLine(file, line, bufp, LOG_BUFFER_SIZE-nSize);
    mWriter.append(mBuffer, nSize);
    //mWriter.append(mBuffer, sizeof(mBuffer));
    *mBuffer = '\0';
}

const char* levelStr[] = 
{
    "DEBUG",
    "TRACE",
    "NOTICE",
    "WARN",
    "ERROR"
};
const char* SyncLogger::leveltoStr(LogLevel level)
{
    if (level < LL_MAX)
	return levelStr[level];
    return "UNKNOWN";
}

size_t SyncLogger::appendDateTime(char* buf, size_t len)
{
    time_t now;
    now = time(&now);
    struct tm vt;
    localtime_r(&now, &vt);
    return snprintf(buf, len, "%04d-%02d-%02d %02d:%02d:%02d ",vt.tm_year+1990,vt.tm_mon+1,vt.tm_mday,vt.tm_hour,vt.tm_min,vt.tm_sec);
}

size_t SyncLogger::appendLogLevel(LogLevel level, char* buf, size_t len)
{
    return snprintf(buf, len, "%s: ",leveltoStr(level));
}

size_t SyncLogger::appendFileLine(const char* file, int line, char* buf, size_t len)
{
    return snprintf(buf, len, " - %s:%d\n", file, line);
}
