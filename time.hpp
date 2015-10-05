#ifndef UNISTD_TIME_HPP
#define UNISTD_TIME_HPP

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
    inline      timespec(decltype(tv_sec) sec, decltype(tv_nsec) nsec);

    //TODO: operator -=, +=, +
    timespec    operator - (const timespec& rvalue) const;
    bool        operator < (const timespec& rvalue) const;
    bool        operator > (const timespec& rvalue) const;
    };

timespec    clock_gettime(clockid_t clk_id);

void        nanosleep(const timespec& req);
void        nanosleep(const timespec& req, timespec& rem);

} //namespace unistd

#include "time.inc"

#endif

