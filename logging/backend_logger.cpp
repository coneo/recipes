#include "backend_logger.h"
#include "log_file.h"
#include <cassert>

using namespace water;

BackendLogger::BackendLogger()
    : m_curBuf(new Buffer)
{
    m_emptyBufs.resize(M_bufReserveSize);
    m_fullBufs.reserve(M_bufReserveSize);
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
	m_fullBufs.push_back(std::move(m_curBuf));
	m_curBuf.reset(new Buffer);
	m_curBuf->put(msg, len);
	//cond.notify();
    }
}

void BackendLogger::threadFunc()
{
    printf("enter threadFunc\n");
    LogFile logFile("./game.log");
    BufferVec writeBufs;
    BufferPtr backBuf(new Buffer);
    while (m_running)
    {
	printf("running");
	assert(writeBufs.size() == 0);
	//cond.wait

	//m_fullBufs.push_back(m_curBuf.release());
	m_fullBufs.push_back(std::move(m_curBuf));
	m_curBuf = std::move(backBuf);
	writeBufs.swap(m_fullBufs);

	for (uint32_t i = 0; i < writeBufs.size(); ++i)
	{
	    logFile.append(writeBufs[i]->data(), writeBufs[i]->length());
	}

	if (!backBuf)
	{
	    assert(writeBufs.size() > 0);
	    backBuf = std::move(writeBufs.back());
	    backBuf->clear();
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
	fprintf(stderr, "error when pthread_create");
    }
    m_running = true;
}
