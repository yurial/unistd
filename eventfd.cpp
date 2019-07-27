#include "eventfd.hpp"
#include <system_error>

namespace unistd
{

int eventfd(unsigned int initval, int flags)
    {
    const int ret = ::eventfd(initval, flags);
    if (-1 == ret)
        throw std::system_error(errno, std::system_category(), "eventfd(...)");
    return ret;
    }

void eventfd_read(int fd, eventfd_t* value)
    {
    const int ret = ::eventfd_read(fd, value);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "eventfd_read(...)");
    }

eventfd_t eventfd_read(int fd)
    {
    eventfd_t value;
    eventfd_read(fd, &value);
    return value;
    }

void eventfd_write(int fd, eventfd_t value)
    {
    const int ret = ::eventfd_write(fd, value);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "eventfd_write(...)");
    }

} // namespace unistd

