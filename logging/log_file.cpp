#include "log_file.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

namespace water{

LogFile::LogFile(std::string filename)
    : m_filename(filename),
      m_fd(1) //标准输出
{
}

LogFile::~LogFile()
{
    ::close(m_fd);
}

bool LogFile::load()
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    m_fd = ::open(m_filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, mode);
    if (-1 == m_fd)
    {
        m_fd = 1; //重新定位到标准输出
        printf("can't open log file: %s\n", m_filename.c_str());
        printf("Error no is: %d\n", errno);
        printf("Error description is:%s\n", strerror(errno));
        return false;
    }
    return true;
}

ssize_t LogFile::writeto(const char* msg, const size_t len)
{
    std::unique_lock<std::mutex> uqlock(m_mutex);
    m_cond.wait(uqlock, [&](){ return lock() != -1;});
    return ::write(m_fd, msg, len);
}

int32_t LogFile::lock()
{
    m_lock.l_type = F_WRLCK;
    return ::fcntl(m_fd, F_SETLK, &m_lock);
}

int32_t LogFile::unlock()
{
    m_lock.l_type = F_UNLCK;
    return ::fcntl(m_fd, F_SETLK, &m_lock);
}

void LogFile::append(const char* msg, const size_t len)
{
    ssize_t n = writeto(msg, len);
    if (-1 == n)
    {
        printf("append log file failed\n");
        printf("Error no is: %d\n", errno);
        printf("Error description is:%s\n", strerror(errno));
        return ;
    }
    size_t rest = len - n;
    while (rest)
    {
        ssize_t rt = writeto(msg + n, rest);
        if (-1 == rt)
        {
            printf("append log file failed\n");
            printf("Error no is: %d\n", errno);
            printf("Error description is:%s\n", strerror(errno));
            break;
        }
        rest -= rt;
    }
}

} //namespace water
