#ifndef UNISTD_NETDB_HPP
#define UNISTD_NETDB_HPP

#include <vector>
#include "addrinfo.hpp"

namespace unistd
{

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, const unistd::addrinfo& hint);
std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, bool passive = false);

int socket(const unistd::addrinfo& addr);
int socket(int domain, int type, int protocol);

void listen(int sock, int backlog);
void bind(int sock, const unistd::addrinfo& addr);
void connect(int sock, const unistd::addrinfo& addr);

void setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen);
template <class T>
void setsockopt(int dockfd, int level, int optname, const T& val);
} //namespace unistd

#include "netdb.inc"

#endif

