namespace unistd
{

timespec::timespec(const ::timespec& origin):
        ::timespec( origin )
    {
    }

timespec::timespec(decltype(tv_sec) sec, decltype(tv_nsec) nsec)
    {
    tv_sec = sec;
    tv_nsec = nsec;
    }

timeval::timeval(const ::timeval& origin):
        ::timeval( origin )
    {
    }

timeval::timeval(decltype(tv_sec) sec, decltype(tv_usec) usec)
    {
    tv_sec = sec;
    tv_usec = usec;
    }

} //namespace unistd

