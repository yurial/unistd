#pragma once
#ifndef UNISTD_NETDB_HPP
#define UNISTD_NETDB_HPP

#include <tuple>
#include <vector>
#include "addrinfo.hpp"
#include "tcp.hpp"

namespace unistd
{

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host_and_port);
std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port,
                                          const unistd::addrinfo& hint);
std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, bool passive = false);

nameinfo getnameinfo(const addrinfo& addr);

int socket(const unistd::addrinfo& addr);
int socket(int domain, int type, int protocol);
std::tuple<int, int> socketpair(int domain, int type, int protocol);

void shutdown(int sock, int how);
void listen(int sock, int backlog);
void bind(int sock, const unistd::addrinfo& addr);
void connect(int sock, const unistd::addrinfo& addr);
int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags=0);
int accept4(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags=0);
int accept(int sockfd, int flags=0);

void setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen);
template <class T>
void setsockopt(int dockfd, int level, int optname, const T& val);
} // namespace unistd

#include "netdb.inc"

#endif
