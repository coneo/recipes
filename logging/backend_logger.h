#ifndef WATER_BASE_BACKEND_LOGGER_HPP
#define WATER_BASE_BACKEND_LOGGER_HPP

namespace water {

class BackendLogger
{
public:
    BackendLogger() = default;
    ~BackendLogger() = default;

    void append(void *msg, uint32_t len);

private:

};

}
#endif //#define WATER_BASE_BACKEND_LOGGER_HPP
