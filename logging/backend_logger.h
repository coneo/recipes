#ifndef WATER_BASE_BACKEND_LOGGER_HPP
#define WATER_BASE_BACKEND_LOGGER_HPP

#include "log_buffer.h"
#include <vector>
#include <memory>
#include <pthread.h>

namespace water {

class BackendLogger
{
public:
    typedef LogBuffer<BIG_BUFFER_SIZE> Buffer;
    typedef std::unique_ptr<Buffer> BufferPtr;
    typedef std::vector<BufferPtr> BufferVec;

    BackendLogger();
    ~BackendLogger();

    void append(const char* msg, uint32_t len);

    void start();

    void stop()
    {
	m_running = false;
	pthread_join(m_threadId, NULL);
    }

    void threadFunc();

private:
    static const uint32_t M_bufReserveSize = 20;
    BufferPtr m_curBuf;
    BufferVec m_emptyBufs;
    BufferVec m_fullBufs;
    bool m_running;
    pthread_t m_threadId;
};

}
#endif //#define WATER_BASE_BACKEND_LOGGER_HPP
