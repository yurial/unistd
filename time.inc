namespace unistd
{

timespec::timespec() noexcept:
        timespec( 0, 0 )
    {
    }

timespec::timespec(const ::timespec& origin) noexcept:
        ::timespec( origin )
    {
    }

timespec::timespec(decltype(::timespec::tv_sec) sec, decltype(::timespec::tv_nsec) nsec) noexcept
    {
    tv_sec = sec;
    tv_nsec = nsec;
    }

timeval::timeval() noexcept:
        timeval( 0, 0 )
    {
    }

timeval::timeval(const ::timeval& origin) noexcept:
        ::timeval( origin )
    {
    }

timeval::timeval(decltype(tv_sec) sec, decltype(tv_usec) usec) noexcept
    {
    tv_sec = sec;
    tv_usec = usec;
    }

} // namespace unistd
