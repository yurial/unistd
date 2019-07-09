#include "netdb.hpp"
#include "internal.hpp"
#include <errno.h>
#include <system_error>

namespace unistd
{

::addrinfo addrinfo_as_native_hint(const addrinfo& addr); // to pass into ::getaddrinfo

// valid input strings:
//   "1.1.1.1:111"
//   "[2a02:6b8::3]:65535"
//   "ya.ru:80"
std::vector<unistd::addrinfo> getaddrinfo(const std::string& host_and_port)
    {
    const size_t first_colon_idx = host_and_port.find(':');
    const size_t last_colon_idx = host_and_port.rfind(':');
    size_t host_start_idx = 0;
    size_t host_end_idx = last_colon_idx;

    if (first_colon_idx == std::string::npos)
        {
        std::string msg = "no colon in " + host_and_port;
        throw std::runtime_error(msg);
        }

    if (first_colon_idx == 0 || last_colon_idx == host_and_port.size() - 1)
        {
        std::string msg = "colon in wrong place in " + host_and_port;
        throw std::runtime_error(msg);
        }

    if (first_colon_idx != last_colon_idx)
        {
        // "[2a02:6b8::3]:80"
        if (host_and_port[0] != '[' || host_and_port[last_colon_idx - 1] != ']')
            {
            std::string msg = "invalid hostport format: " + host_and_port;
            throw std::runtime_error(msg);
            }
        host_start_idx++;
        host_end_idx--;
        }

    long port = atol(host_and_port.substr(last_colon_idx + 1).c_str());
    if (port < 0 || port > 65535)
        {
        std::string msg = "invalid port in " + host_and_port;
        throw std::runtime_error(msg);
        }

    return getaddrinfo(host_and_port.substr(host_start_idx, host_end_idx - host_start_idx), host_and_port.substr(last_colon_idx + 1));
}

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, bool passive)
    {
    unistd::addrinfo hint;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = passive? AI_PASSIVE : 0;
    return unistd::getaddrinfo(host, port, hint);
    }

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, const unistd::addrinfo& hint)
    {
    ::addrinfo native_hint = addrinfo_as_native_hint(hint);
    ::addrinfo* res = nullptr;
    const int ret = ::getaddrinfo(host.c_str(), port.c_str(), &native_hint, &res);
    if (ret != 0)
        {
        if (ret == EAI_SYSTEM)
            throw std::system_error(errno, std::system_category(), internal::mkstr("getaddrinfo('%s'): ", host.c_str()));
        else
            throw std::runtime_error(internal::mkstr("getaddrinfo('%s'): %s", host.c_str(), ::gai_strerror(ret)));
        }

    std::vector<unistd::addrinfo> result;
    for (::addrinfo* cur = res; cur; cur = cur->ai_next)
        result.push_back(*cur);

    for (auto& addr: result)
        {
        addr.ai_host = host;
        addr.ai_port = port;
        }

    freeaddrinfo(res);
    return result;
    }

nameinfo getnameinfo(const addrinfo& addr)
    {
    char host_buf[NI_MAXHOST];
    char serv_buf[NI_MAXSERV];

    const int ret = ::getnameinfo(reinterpret_cast<const sockaddr*>(&addr.ai_addr), addr.ai_addrlen, host_buf,
                            sizeof(host_buf), serv_buf, sizeof(serv_buf), NI_NUMERICHOST | NI_NUMERICSERV);
    if (ret != 0)
        {
        if (ret == EAI_SYSTEM)
            throw std::system_error(errno, std::system_category(), "getnameinfo");
        else
            throw std::runtime_error(internal::mkstr("getnameinfo(): %s", ::gai_strerror(ret)));
        }

    nameinfo result;
    result.host = host_buf;
    result.serv = serv_buf;
    return result;
    }

::addrinfo addrinfo_as_native_hint(const addrinfo& addr)
    {
    // According to docs only ai_family, ai_socktype, ai_protocol and ai_flags must be set
    ::addrinfo result;
    ::memset(&result, 0, sizeof(result));
    result.ai_flags = addr.ai_flags;
    result.ai_family = addr.ai_family;
    result.ai_socktype = addr.ai_socktype;
    result.ai_protocol = addr.ai_protocol;
    return result;
    }

int socket(const unistd::addrinfo& addr)
    {
    return unistd::socket(addr.ai_family, addr.ai_socktype, addr.ai_protocol);
    }

int socket(int domain, int type, int protocol)
    {
    const int fd = ::socket(domain, type, protocol);
    if (-1 == fd)
        throw std::system_error(errno, std::system_category(), "socket");
    return fd;
    }

std::tuple<int, int> socketpair(int domain, int type, int protocol)
    {
    int sv[2] = {-1, -1};
    const int ret = ::socketpair(domain, type, protocol, sv);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "socketpair");
    return std::make_tuple(sv[0], sv[1]);
    }

void shutdown(int sock, int how)
    {
    const int ret = ::shutdown(sock, how);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "shutdown");
    }

void listen(int sock, int backlog)
    {
    const int ret = ::listen(sock, backlog);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "listen");
    }

void bind(int sock, const unistd::addrinfo& addr)
    {
    const int ret = ::bind(sock, reinterpret_cast<const sockaddr*>(&addr.ai_addr), addr.ai_addrlen);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "bind");
    }

void connect(int sock, const unistd::addrinfo& addr)
    {
    const int ret = ::connect(sock, reinterpret_cast<const sockaddr*>(&addr.ai_addr), addr.ai_addrlen);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "connect");
    }

int accept4(int sockfd, struct sockaddr* addr, socklen_t* addrlen, int flags)
    {
    const int fd = ::accept4(sockfd, addr, addrlen, flags);
    if (-1 == fd)
        throw std::system_error(errno, std::system_category(), "accept4");
    return fd;
    }

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags)
    {
    return unistd::accept4(sockfd, addr, addrlen, flags);
    }

int accept(int sockfd, int flags)
    {
    return unistd::accept(sockfd, nullptr, 0, flags);
    }

void setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen)
    {
    const int ret = ::setsockopt(sockfd, level, optname, optval, optlen);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), "setsockopt");
    }

} // namespace unistd

