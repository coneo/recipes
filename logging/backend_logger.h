#ifndef WATER_BASE_BACKEND_LOGGER_HPP
#define WATER_BASE_BACKEND_LOGGER_HPP

#include "log_buffer.h"
#include <vector>

namespace water {

class BackendLogger
{
public:
    typedef LogBuffer<BIG_BUFFER_SIZE> Buffer;
    typedef std::unique_ptr<Buffer> BufferPtr;
    typedef std::vector<BufferPtr> BufferVec;

    void append(const char* msg, uint32_t len);

    void start();

    void threadFunc();

private:
    BackendLogger();
    ~BackendLogger();

private:
    static const BUFFER_RESERVE_SIZE = 20;
    BufferPtr m_curBuf;
    BufferVec m_emptyBufs;
    BufferVec m_fullBufs;
    bool m_running;
};

}
#endif //#define WATER_BASE_BACKEND_LOGGER_HPP
