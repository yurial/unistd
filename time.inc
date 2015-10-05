namespace unistd
{

timespec::timespec(decltype(tv_sec) sec, decltype(tv_nsec) nsec)
    {
    tv_sec = sec;
    tv_nsec = nsec;
    }

} //namespace unistd

