#ifndef WATER_BASE_LOG_FILE_HPP
#define WATER_BASE_LOG_FILE_HPP

#include <string>

namespace water {

class LogFile
{
public:
    LogFile(std::string name);
    ~LogFile();

    bool load();

    ssize_t writeto(const char* msg, const size_t line);

    void append(const char* msg, const size_t line);

private:
    std::string m_filename;
    int m_fd;
};
}

#endif //#define WATER_BASE_LOG_FILE_HPP

