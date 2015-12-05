#ifndef _FORMAT_H
#define _FORMAT_H

#include <string>
#include <sstream>

void formatImp(std::ostringstream& oss, const char* fmt)
{
    if (!fmt) return ;

    while (*fmt)
    {
        if (*fmt != '{')
        {
            oss << *fmt++;
            continue;
        }

        oss << "[fmt error, miss args]";
        return ;
    }
}

template <typename T, typename ...Args>
void formatImp(std::ostringstream& oss, const char* fmt, T& value, Args... args)
{
    if (!fmt) return ;

    while (*fmt)
    {
        if (*fmt != '{')
        {
            oss << *fmt++;
            continue;
        }

        while (*fmt)
        {
            if (*fmt == '}')
            {
                oss << value;
                formatImp(oss, *fmt ? ++fmt : fmt, args...);
                return ;
            }
            ++fmt;
        }
    }
}

template <typename ...Args>
void format(std::string& ret, Args... args)
{
    std::ostringstream oss;
    formatImp(oss, args...);
    ret.append(oss.str());
}

#endif
