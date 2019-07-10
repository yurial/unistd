#pragma once

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

namespace unistd
{
struct timespec:
    public ::timespec
{
using ::timespec::tv_nsec;
using ::timespec::tv_sec;

inline timespec() noexcept;
inline timespec(const ::timespec& origin) noexcept;
inline timespec(decltype(::timespec::tv_sec) sec, decltype(::timespec::tv_nsec) nsec) noexcept;

timespec    operator + (const timespec& rvalue) const noexcept;
timespec    operator - (const timespec& rvalue) const noexcept;
timespec&   operator +=(const timespec& rvalue) noexcept;
// TODO: timespec&   operator -=(const timespec& rvalue) noexcept;
bool        operator < (const timespec& rvalue) const noexcept;
bool        operator > (const timespec& rvalue) const noexcept;
bool        operator ==(const timespec& rvalue) const noexcept;
bool        operator <=(const timespec& rvalue) const noexcept;
bool        operator >=(const timespec& rvalue) const noexcept;
};

struct timeval:
    public ::timeval
{
using ::timeval::tv_sec;
using ::timeval::tv_usec;

inline      timeval() noexcept;
inline      timeval(const ::timeval& origin) noexcept;
inline      timeval(decltype(tv_sec) sec, decltype(tv_usec) usec) noexcept;

//TODO: operator -=, +=
timeval     operator +  (const timeval& rvalue) const noexcept;
timeval     operator -  (const timeval& rvalue) const noexcept;
bool        operator <  (const timeval& rvalue) const noexcept;
bool        operator >  (const timeval& rvalue) const noexcept;
bool        operator <= (const timeval& rvalue) const noexcept;
bool        operator >= (const timeval& rvalue) const noexcept;
}; // struct timeval

timespec clock_gettime(const clockid_t clk_id);

void nanosleep(const timespec& req);
void nanosleep(const timespec& req, timespec& rem);

} // namespace unistd

#include "time.inc"

