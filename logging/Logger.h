/*
 * format : data time level msg file line 
 * example: 2014-07-27 09:41:23 DEBUG: hello shok - Loggging_test.cpp:34
 *
 */
#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>

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

    void log(LogLevel level, char* format, ...);

    void formatTime();

    void setLogLevel(LogLevel l){ mLevel = l; }
    LogLevel level() const { return mLevel; }
    const char* getLevelStr();

public:
    void print(const char* s)
    {
        while (*s)
        {
            if (*s == '%' && *++s != '%')
                throw std::runtime_error("miss arg");
            std::cout << *s++;
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
                std::cout << value;
                return print(++s, args...);
            }
            std::cout << *s++;
        }
        throw std::runtime_error("extra arg");
    }

public:
    typedef std::function<void ()> AppendCallback;
    void setAppendCallback(AppendCallback cb){ mAppendcb = cb; }

private:
    AppendCallback mAppendcb;
    LogLevel mLevel;
};

extern Logger gLogger;

/*
#define LOG_DEBUG(log_fmt, log_arg...) \
	do{\
        gLogger.log(LL_DEBUG, ""log_fmt" %s,%d \n", \
                ##log_arg, __FILE__,__LINE__); \
	}while(0)

*/
