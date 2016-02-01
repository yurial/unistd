namespace unistd
{

template <class T>
void setsockopt(int sockfd, int level, int optname, const T& val)
    {
    unistd::setsockopt( sockfd, level, optname, &val, sizeof(val) );
    }

} //namespace unistd

