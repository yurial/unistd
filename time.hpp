#ifndef UNISTD_TIME_HPP
#define UNISTD_TIME_HPP

#include <sys/time.h>
#include <time.h>
#include <unistd.h>


namespace unistd
{
struct timespec:
        public ::timespec
    {
    using ::timespec::tv_sec;
    using ::timespec::tv_nsec;

                timespec() = default;
    inline      timespec(const ::timespec& origin);
    inline      timespec(decltype(tv_sec) sec, decltype(tv_nsec) nsec);

    //TODO: operator -=, +=
    timespec    operator +  (const timespec& rvalue) const;
    timespec    operator -  (const timespec& rvalue) const;
    bool        operator <  (const timespec& rvalue) const;
    bool        operator >  (const timespec& rvalue) const;
    bool        operator <= (const timespec& rvalue) const;
    bool        operator >= (const timespec& rvalue) const;
    }; //struct timespec

struct timeval:
        public ::timeval
    {
    using ::timeval::tv_sec;
    using ::timeval::tv_usec;

                timeval() = default;
    inline      timeval(const ::timeval& origin);
    inline      timeval(decltype(tv_sec) sec, decltype(tv_usec) usec);

    //TODO: operator -=, +=
    timeval     operator +  (const timeval& rvalue) const;
    timeval     operator -  (const timeval& rvalue) const;
    bool        operator <  (const timeval& rvalue) const;
    bool        operator >  (const timeval& rvalue) const;
    bool        operator <= (const timeval& rvalue) const;
    bool        operator >= (const timeval& rvalue) const;
    }; // struct timeval

timespec    clock_gettime(clockid_t clk_id);

void        nanosleep(const timespec& req);
void        nanosleep(const timespec& req, timespec& rem);

} //namespace unistd

#include "time.inc"

#endif

