#include <errno.h>
#include <system_error>

#include "time.hpp"

namespace unistd
{

timespec timespec::operator - (const timespec& rvalue) const
{
timespec result = *this;;
result.tv_sec -= rvalue.tv_sec;
result.tv_nsec -= rvalue.tv_nsec;
if ( result.tv_nsec < 0 )
    {
    --result.tv_sec;
    result.tv_nsec += 1000 * 1000 * 1000;
    }
return result;
}

bool timespec::operator < (const timespec& rvalue) const
{
if ( tv_sec < rvalue.tv_sec )
    return true;
else if ( rvalue.tv_sec < tv_sec )
    return false;
else if ( tv_nsec < rvalue.tv_nsec )
    return true;
return false;
}

bool timespec::operator > (const timespec& rvalue) const
{
return rvalue < *this;
}


timespec clock_gettime(clockid_t clk_id)
{
timespec result;
int ret = clock_gettime( clk_id, &result );
if ( 0 != ret )
    throw std::system_error( errno, std::system_category(), "clock_gettime" );
return result;
}

void nanosleep(const timespec& req)
{
int ret = ::nanosleep( &req, nullptr );
if ( 0 != ret )
    throw std::system_error( errno, std::system_category(), "nanosleep" );
}

void nanosleep(const timespec& req, timespec& rem)
{
int ret = ::nanosleep( &req, &rem );
if ( 0 != ret )
    throw std::system_error( errno, std::system_category(), "nanosleep" );
}

} //namespace unistd

