/*
 * format : data time level msg file line 
 * example: 2014-07-27 09:41:23 DEBUG: hello shok - Loggging_test.cpp:34
 *
 */
#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <time.h>

enum LogLevel
{
	LL_DEBUG,
	LL_TRACE,
	LL_NOTICE,
	LL_WARN,
	LL_ERROR,
	LL_MAX
};

class Logger
{
public:
    Logger();
    ~Logger();

    template<typename... Args>
    void log(LogLevel level, const char* file, int line,  Args... args)
    {
	mStream << getLevelStr(level) << ": ";
	print(args...);
	mStream << " - " << file << ":" << line;
	mStream << "\n";
    }

    void formatTime();

    void setLogLevel(LogLevel l){ mLevel = l; }
    LogLevel level() const { return mLevel; }
    const char* getLevelStr(LogLevel l);

public:
    void print(const char* s)
    {
        while (*s)
        {
            if (*s == '%' && *++s != '%')
                throw std::runtime_error("miss arg");
            mStream << *s++;
        }
    }

    //how about print(int ,std::string, struct s ...);
    template<typename T, typename... Args>
    void print(const char* s, T value, Args... args)
    {
        while (*s)
        {
            if (*s == '%' && *++s != '%')
            {
                mStream << value;
                return print(++s, args...);
            }
            mStream << *s++;
        }
        throw std::runtime_error("extra arg");
    }

    void printout()
    {
	std::cout << mStream.str();
	mStream.clear();
    }
public:
    typedef std::function<void ()> AppendCallback;
    typedef std::stringstream LogStream;

public:
    void setAppendCallback(AppendCallback cb){ mAppendcb = cb; }

private:
    AppendCallback mAppendcb;
    LogLevel mLevel;
    LogStream mStream;
};

extern Logger gLogger;

#define LOG_DEBUG(...) \
	do{\
        gLogger.log(LL_DEBUG, __FILE__,__LINE__, __VA_ARGS__); \
	}while(0)

#define LOG_TRACE(...) \
	do{\
        gLogger.log(LL_TRACE, __FILE__,__LINE__, __VA_ARGS__); \
	}while(0)
