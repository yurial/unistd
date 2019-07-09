#include <system_error>

namespace unistd
{

inline int signalfd(int fd, const sigset_t* mask, int flags)
    {
    int newfd = ::signalfd( fd, mask, flags );
    if ( -1 == newfd )
        throw std::system_error( errno, std::system_category(), "signalfd_cleate" );
    return newfd;
    }

inline int signalfd(const sigset_t* mask, int flags)
    {
    return unistd::signalfd( -1, mask, flags );
    }

inline int signalfd(int fd, const sigset_t& mask, int flags)
    {
    return unistd::signalfd( fd, &mask, flags );
    }

inline int signalfd(const sigset_t& mask, int flags)
    {
    return unistd::signalfd( -1, mask, flags );
    }

} //namespace unistd

