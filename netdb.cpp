#include <errno.h>
#include <string.h>
#include <system_error>
#include <ext/mkstr.hpp>
#include "netdb.hpp"

namespace unistd
{

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, bool passive)
    {
    unistd::addrinfo hint;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = passive? AI_PASSIVE : 0;
    return unistd::getaddrinfo( host, port, hint );
    }

std::vector<unistd::addrinfo> getaddrinfo(const std::string& host, const std::string& port, const unistd::addrinfo& hint)
    {
    struct ::addrinfo native_hint = hint;
    struct ::addrinfo* res = nullptr;
    int ret = getaddrinfo( host.c_str(), port.c_str(), &native_hint, &res ); 
    if ( 0 != ret )
        throw std::runtime_error( ext::mkstr( "getaddrinfo('%s'): %s", host.c_str(), gai_strerror( ret ) ) );

    std::vector<unistd::addrinfo> result;
    for (; res; res = res->ai_next)
        result.push_back( *res );

    freeaddrinfo( res );
    return result;
    }

int socket(const unistd::addrinfo& addr)
    {
    return unistd::socket( addr.ai_family, addr.ai_socktype, addr.ai_protocol );
    }

int socket(int domain, int type, int protocol)
    {
    int fd = ::socket( domain, type, protocol );
    if ( -1 == fd )
        throw std::system_error( errno, std::system_category(), "socket" );
    return fd;
    }

void listen(int sock, int backlog)
    {
    int ret = ::listen( sock, backlog );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "listen" );
    }

void bind(int sock, const unistd::addrinfo& addr)
    {
    int ret = ::bind( sock, reinterpret_cast<const sockaddr*>( &addr.ai_addr ), addr.ai_addrlen );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "bind" );
    }

void connect(int sock, const unistd::addrinfo& addr)
    {
    int ret = ::connect( sock, reinterpret_cast<const sockaddr*>( &addr.ai_addr ), addr.ai_addrlen );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "connect" );
    }

void setsockopt(int sockfd, int level, int optname, const void* optval, socklen_t optlen)
    {
    int ret = ::setsockopt( sockfd, level, optname, optval, optlen );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), "setsockopt" );
    }

} //namespace unistd

