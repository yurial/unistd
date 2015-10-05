namespace unistd
{

inline int epoll_create(int flags)
    {
    int fd = ::epoll_create1( flags );
    if ( -1 == fd )
        throw std::system_error( errno, std::system_category(), "epoll_create1" );
    return fd;
    }

inline void epoll_ctl(int efd, int op, int fd, const struct epoll_event* event)
    {
    int ret = ::epoll_ctl( efd, op, fd, const_cast<struct epoll_event*>( event ) );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "epoll_ctl" );
    }

inline size_t epoll_wait(int efd, struct epoll_event* events, int maxevents, int timeout)
    {
    int nready = ::epoll_wait( efd, events, maxevents, timeout );
    if ( nready < 0 )
        throw std::system_error( errno, std::system_category(), "epoll_wait" );
    return nready;
    }

inline void epoll_ctl(int efd, int op, int fd, int events, int arg_fd)
    {
    struct epoll_event data;
    data.events = events;
    data.data.fd = arg_fd;
    ::unistd::epoll_ctl( efd, op, fd, &data );
    }

inline void epoll_ctl(int efd, int op, int fd, int events, void* arg_ptr)
    {
    struct epoll_event data;
    data.events = events;
    data.data.ptr = arg_ptr;
    ::unistd::epoll_ctl( efd, op, fd, &data );
    }

inline void epoll_ctl(int efd, int op, int fd, int events, uint32_t arg_u32)
    {
    struct epoll_event data;
    data.events = events;
    data.data.u32 = arg_u32;
    ::unistd::epoll_ctl( efd, op, fd, &data );
    }

inline void epoll_ctl(int efd, int op, int fd, int events, uint64_t arg_u64)
    {
    struct epoll_event data;
    data.events = events;
    data.data.u64 = arg_u64;
    ::unistd::epoll_ctl( efd, op, fd, &data );
    }

template <class T>
inline void epoll_add(int efd, int fd, int events, const T& arg)
    {
    ::unistd::epoll_ctl( efd, EPOLL_CTL_ADD, fd, events, arg );
    }

template <class T>
inline void epoll_mod(int efd, int fd, int events, const T& arg)
    {
    ::unistd::epoll_ctl( efd, EPOLL_CTL_MOD, fd, events, arg );
    }

template <class T>
inline void epoll_del(int efd, int fd, int events, const T& arg)
    {
    ::unistd::epoll_ctl( efd, EPOLL_CTL_DEL, fd, events, arg );
    }

inline void epoll_wait(int efd, std::vector<epoll_event>& events, int timeout)
    {
    int nready = ::unistd::epoll_wait( efd, events.data(), events.size(), timeout );
    events.resize( nready );
    }

inline std::vector<epoll_event> epoll_wait(int efd, int maxevents, int timeout)
    {
    std::vector<epoll_event> events( maxevents );
    unistd::epoll_wait( efd, events, timeout );
    return events;
    }

} //namespace unistd

