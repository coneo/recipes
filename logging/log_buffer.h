#ifndef WATER_BASE_LOG_BUFFER_HPP
#define WATER_BASE_LOG_BUFFER_HPP

#include <stdint.h>
#include <string.h>

namespace water {

const uint32_t BIG_BUFFER_SIZE = 4000 * 1000;

template <uint32_t SIZE>
class LogBuffer
{
public:
    LogBuffer() 
    : m_cur(m_data)
    {
        bzero(m_data, sizeof(m_data));
    }
    ~LogBuffer() = default;

    void put(const char* msg, uint32_t len)
    {
        if (remain() > len)
        {
            memcpy(m_cur, msg, len);
            m_cur += len;
        }
    }

    const char* data() { return m_data; }

    uint32_t length() const { return m_cur - m_data; }

    uint32_t remain() const { return static_cast<uint32_t>(end() - m_cur); }
    void reset() { m_cur = m_data; }

private:
    const char* end() const { return m_data + sizeof(m_data); }

private:
    char m_data[SIZE];
    char* m_cur;
};
}
#endif //#define WATER_BASE_LOG_BUFFER_HPP

