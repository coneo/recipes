#ifndef _PERFORMANCE_KIT_H
#define _PERFORMANCE_KIT_H

#include <chrono>
#include <string>
#include <iostream>

/*
 * 消耗统计，采用RAII管理
 * 使用方法：time_count t("描述");
 */
class time_count
{
public:
    time_count(std::string desc_) :
      desc(desc_)
    {
        start = std::chrono::system_clock::now();
    }

    ~time_count()
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << desc << ":" << double(duration.count()) << " " << "毫秒"<< std::endl;
    }

private:
    std::chrono::system_clock::time_point start;
    std::string desc;
};

/*
 * 函数调用指定次数
 */
#define CALL_TIMES(times, func)\
{\
    for (int index_of_i = 0; index_of_i < times; ++index_of_i)\
    {\
        func\
    }\
}\

/*
 * 函数调用指定次数,并统计时间
 */
#define CALL_TIMES_AND_TIME(times, desc, func)\
{\
    time_count t(desc);\
    for (int index_of_i = 0; index_of_i < times; ++index_of_i)\
    {\
        func;\
    }\
}\

#endif // _PERFORMANCE_KIT_H
