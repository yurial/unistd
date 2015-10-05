namespace unistd
{

template <class T>
void setsockopt(int sockfd, int level, int optname, const T& val)
    {
    setsockopt( sockfd, level, optname, &val, sizeof(val) );
    }

} //namespace unistd

