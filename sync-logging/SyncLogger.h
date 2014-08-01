#pragma once

#include "WriteFile.h"
#include <stdlib.h>

#define LOG_BUFFER_SIZE 1024*4

enum LogLevel
{
	LL_DEBUG,
	LL_TRACE,
	LL_NOTICE,
	LL_WARN,
	LL_ERROR,
	LL_MAX
};

class SyncLogger
{
public:
    SyncLogger(const char* filename);
    ~SyncLogger() = default;

    void log(LogLevel level, const char* file, int line, const char* fmt, ...);

    const char* leveltoStr(LogLevel level);

    void setLogLevel(LogLevel level) { mLevel = level; }

    bool compare(LogLevel level){ return level >= mLevel; }

private:
    size_t appendDateTime(char* buf, size_t len);

    size_t appendLogLevel(LogLevel level, char* buf, size_t len);

    size_t appendFileLine(const char* file, int line, char* buf, size_t len);

private:
    LogLevel mLevel;
    WriteFile mWriter; //file writer
    static __thread char mBuffer[LOG_BUFFER_SIZE];
};

extern SyncLogger gLogger;

#define LOG_DEBUG(fmt, arg...) \
	do{\
	    gLogger.log(LL_DEBUG, __FILE__,__LINE__, fmt, ##arg); \
	}while(0)
#define LOG_TRACE(fmt, arg...) \
	do{\
	    gLogger.log(LL_TRACE, __FILE__,__LINE__, fmt, ##arg); \
	}while(0)
#define LOG_NOTICE(fmt, arg...) \
	do{\
	    gLogger.log(LL_NOTICE, __FILE__,__LINE__, fmt, ##arg); \
	}while(0)
#define LOG_WARN(fmt, arg...) \
	do{\
	    gLogger.log(LL_WARN, __FILE__,__LINE__, fmt, ##arg); \
	}while(0)
#define LOG_ERROR(fmt, arg...) \
	do{\
	    gLogger.log(LL_ERROR, __FILE__,__LINE__, fmt, ##arg); \
	}while(0)
