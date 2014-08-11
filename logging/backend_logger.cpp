#include "backend_logger.h"
#include "log_file.h"
#include <time.h>
#include <cassert>

using namespace water;

BackendLogger::BackendLogger()
    : m_curBuf(new Buffer),
      m_mutex(PTHREAD_MUTEX_INITIALIZER),
      m_cond(PTHREAD_COND_INITIALIZER)
{
    m_fullBufs.reserve(M_bufReserveSize);
    m_emptyBufs.resize(M_bufReserveSize);
    for (uint32_t i = 0; i < m_emptyBufs.size(); ++i)
        m_emptyBufs[i].reset(new Buffer);
}

BackendLogger::~BackendLogger()
{
}

void BackendLogger::append(const char* msg, uint32_t len)
{
    if (m_curBuf->remain() > len)
    {
        m_curBuf->put(msg, len);
    }
    else
    {
#ifdef _HXQ_DEBUG
        printf("%s,%s",__func__, "new buf");
#endif
        m_fullBufs.push_back(std::move(m_curBuf));
        if (m_emptyBufs.size() > 0)
        {
            m_curBuf = std::move(m_emptyBufs.back());
            m_emptyBufs.pop_back();
        }
        else
        {
            //throw error
            printf("mo more buffers\n");
        }
        m_curBuf->put(msg, len);
        pthread_cond_signal(&m_cond);
    }
}

void BackendLogger::threadFunc()
{
#ifdef _HXQ_DEBUG
    printf("enter threadFunc\n");
#endif
    LogFile logFile("./game.log");
    logFile.load();
    BufferVec writeBufs;
    BufferVec backBufs;
    backBufs.resize(M_bufReserveSize);
    for (uint32_t i = 0; i < backBufs.size(); ++i)
        backBufs[i].reset(new Buffer);

    while (m_running)
    {
        pthread_mutex_lock(&m_mutex);
        assert(writeBufs.size() == 0);
        assert(backBufs.size() == M_bufReserveSize);
        if(m_fullBufs.empty())
        {
            //cond_wait
            struct timespec abstime;
            clock_gettime(CLOCK_REALTIME, &abstime);
            abstime.tv_sec += 2;
            pthread_cond_timedwait(&m_cond,&m_mutex,&abstime);
        }

        m_fullBufs.push_back(std::move(m_curBuf));
        if (backBufs.size() > 0)
        {
            m_curBuf = std::move(backBufs.back());
            backBufs.pop_back();
        }
        writeBufs.swap(m_fullBufs);
        pthread_mutex_unlock(&m_mutex);

        for (uint32_t i = 0; i < writeBufs.size(); ++i)
        {
            logFile.append(writeBufs[i]->data(), writeBufs[i]->length());
            writeBufs[i]->reset();
        }

        while (m_emptyBufs.size() < M_bufReserveSize && backBufs.size() > 0)
        {
            m_emptyBufs.push_back(std::move(backBufs.back()));
            backBufs.pop_back();
        }
        while (backBufs.size() < M_bufReserveSize && writeBufs.size() > 0)
        {
            backBufs.push_back(std::move(writeBufs.back()));
            writeBufs.pop_back();
        }
        writeBufs.clear();
    }
}

void* runThread(void* obj)
{
    BackendLogger* bkLogger = reinterpret_cast<BackendLogger*>(obj);
    bkLogger->threadFunc();
    return NULL;
}

void BackendLogger::start()
{
    if (pthread_create(&m_threadId, NULL, &runThread, this))
    {
        fprintf(stderr, "error when pthread_create,%s",__func__);
    }
    m_running = true;
}
