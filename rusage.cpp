#include <sys/time.h>
#include <errno.h>
#include <system_error>

#include "rusage.hpp"

namespace unistd
{

::rusage getrusage(int who)
    {
    ::rusage usage;
    int ret = ::getrusage( who, &usage );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "getrusage" );
    return usage;
    }

} //namespace unistd

