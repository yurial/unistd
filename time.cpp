#include "time.hpp"
#include <errno.h>
#include <system_error>
#include <tuple>

namespace unistd
{

timespec timespec::operator + (const timespec& rvalue) const noexcept
    {
    timespec result = *this;
    result.tv_sec += rvalue.tv_sec;
    result.tv_sec += (result.tv_nsec + rvalue.tv_nsec) / 1000000000L;
    result.tv_nsec = (result.tv_nsec + rvalue.tv_nsec) % 1000000000L;
    return result;
    }

timespec timespec::operator - (const timespec& rvalue) const noexcept
    {
    timespec result = *this;

    result.tv_sec -= rvalue.tv_sec;
    result.tv_nsec -= rvalue.tv_nsec;
    if (result.tv_nsec < 0)
        {
        --result.tv_sec;
        result.tv_nsec += 1000 * 1000 * 1000;
        }
    return result;
    }

timespec& timespec::operator += (const timespec& rvalue) noexcept
    {
    tv_sec += rvalue.tv_sec;
    tv_nsec += rvalue.tv_nsec;
    if (tv_nsec >= 1000 * 1000 * 1000)
        {
        tv_sec++;
        tv_nsec -= 1000 * 1000 * 1000;
        }
    return *this;
    }

bool timespec::operator < (const timespec& rvalue) const noexcept
    {
    return std::tie(tv_sec, tv_nsec) < std::tie(rvalue.tv_sec, rvalue.tv_nsec);
    }

bool timespec::operator <= (const timespec& rvalue) const noexcept
    {
    return std::tie(tv_sec, tv_nsec) <= std::tie(rvalue.tv_sec, rvalue.tv_nsec);
    }

bool timespec::operator >= (const timespec& rvalue) const noexcept
    {
    return std::tie(tv_sec, tv_nsec) >= std::tie(rvalue.tv_sec, rvalue.tv_nsec);
    }

bool timespec::operator > (const timespec& rvalue) const noexcept
    {
    return rvalue < *this;
    }

bool timespec::operator == (const timespec& rvalue) const noexcept
    {
    return tv_sec == rvalue.tv_sec && tv_nsec == rvalue.tv_nsec;
    }

timeval timeval::operator + (const timeval& rvalue) const noexcept
    {
    timeval result = *this;
    result.tv_sec += rvalue.tv_sec;
    result.tv_sec += (result.tv_usec + rvalue.tv_usec) / 1000000L;
    result.tv_usec = (result.tv_usec + rvalue.tv_usec) % 1000000L;
    return result;
    }

timeval timeval::operator - (const timeval& rvalue) const noexcept
    {
    timeval result = *this;;
    result.tv_sec -= rvalue.tv_sec;
    result.tv_usec -= rvalue.tv_usec;
    if ( result.tv_usec < 0 )
        {
        --result.tv_sec;
        result.tv_usec += 1000 * 1000;
        }
    return result;
    }

bool timeval::operator < (const timeval& rvalue) const noexcept
    {
    return std::tie(tv_sec, tv_usec) < std::tie(rvalue.tv_sec, rvalue.tv_usec);
    }

bool timeval::operator > (const timeval& rvalue) const noexcept
    {
    return rvalue < *this;
    }

bool timeval::operator <= (const timeval& rvalue) const noexcept
    {
    return std::tie(tv_sec, tv_usec) <= std::tie(rvalue.tv_sec, rvalue.tv_usec);
    }

bool timeval::operator >= (const timeval& rvalue) const noexcept
    {
    return rvalue <= *this;
    }

timespec clock_gettime(const clockid_t clk_id)
    {
    timespec result;
    const int ret = clock_gettime(clk_id, &result);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "clock_gettime");
    return result;
    }

void nanosleep(const timespec& req)
    {
    const int ret = ::nanosleep(&req, nullptr);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "nanosleep");
    }

void nanosleep(const timespec& req, timespec& rem)
    {
    const int ret = ::nanosleep(&req, &rem);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "nanosleep");
    }

} // namespace unistd

