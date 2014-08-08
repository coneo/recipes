#ifndef WATER_BASE_LOG_FILE_HPP
#define WATER_BASE_LOG_FILE_HPP

#include <string>

namespace water {

class LogFile
{
public:
    LogFile(std::string name);
    ~LogFile();

    size_t write(const char* msg, const size_t line);

    void append(const char* msg, const size_t line);

    void flush();

private:

    FILE* fp;
};
}

#endif //#define WATER_BASE_LOG_FILE_HPP

