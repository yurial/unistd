#ifndef UNISTD_EPOLL_HPP
#define UNISTD_EPOLL_HPP

#include <sys/epoll.h>
#include <errno.h>
#include <system_error>
#include <vector>

namespace unistd
{

int     epoll_create(int flags = 0);

void    epoll_ctl(int efd, int op, int fd, const struct epoll_event* event);
void    epoll_ctl(int efd, int op, int fd, int events, int arg_fd);
void    epoll_ctl(int efd, int op, int fd, int events, void* arg_ptr);
void    epoll_ctl(int efd, int op, int fd, int events, uint32_t arg_u32);
void    epoll_ctl(int efd, int op, int fd, int events, uint64_t arg_u64);

size_t  epoll_wait(int efd, struct epoll_event* events, int maxevents, int timeout);

template <class T>
void    epoll_add(int efd, int fd, int events, const T& arg);
template <class T>
void    epoll_mod(int efd, int fd, int events, const T& arg);
template <class T>
void    epoll_del(int efd, int fd, int events, const T& arg);

void    epoll_wait(int efd, std::vector<epoll_event>& events, int timeout);
std::vector<epoll_event> epoll_wait(int efd, int maxevents, int timeout);

} //namespace unistd

#include "epoll.inc"

#endif

