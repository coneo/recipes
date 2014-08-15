#ifndef WATER_BASE_LOG_FILE_HPP
#define WATER_BASE_LOG_FILE_HPP

#include <string>
#include <fcntl.h>
#include <condition_variable>

namespace water {

class LogFile
{
public:
    LogFile(std::string name);
    ~LogFile();

    bool load();

    ssize_t writeto(const char* msg, const size_t line);

    int32_t lock();

    int32_t unlock();

    void append(const char* msg, const size_t line);

private:
    std::string m_filename;
    int32_t m_fd;
    struct flock m_lock { F_WRLCK, SEEK_SET, 0, 0, 0 };
    std::mutex m_mutex;
    std::condition_variable m_cond;
};
}

#endif //#define WATER_BASE_LOG_FILE_HPP

