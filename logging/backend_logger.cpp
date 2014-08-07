#include "backend_logger.h"

using namespace water;

BackendLogger::BackendLogger()
    : m_curBuf(new Buffer)
{
    m_emptyBufs.resize(BUFFER_RESERVE_SIZE);
    m_fullBufs.reserve(BUFFER_RESERVE_SIZE);
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
	if (m_emptyBufs.size() > 0)
	{
	    m_curBuf = std::move(m_emptyBufs.pop_back());
	}
	else
	{
	    //throw exception
	}
	m_curBuf->put(msg, len);
	//cond.notify();
    }
}
