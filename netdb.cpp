#include <errno.h>
#include <string.h>
#include <system_error>
#include <ext/mkstr.hpp>
#include "netdb.hpp"

namespace unistd
{

// valid input strings:
//   "1.1.1.1:111"
//   "[2a02:6b8::3]:65535"
//   "ya.ru:80"
std::vector<unistd::addrinfo> getaddrinfo(const std::string& host_and_port)
    {
    size_t first_colon_idx = host_and_port.find(':');
    size_t last_colon_idx  = host_and_port.rfind(':');
    size_t host_start_idx  = 0;
    size_t host_end_idx    = last_colon_idx;

    if( first_colon_idx == std::string::npos )
        {
        std::string msg = "no colon in " + host_and_port;
        throw std::runtime_error(msg);
        }

    if( first_colon_idx == 0 || last_colon_idx == host_and_port.size()-1 )
        {
        std::string msg = "colon in wrong place in " + host_and_port;
        throw std::runtime_error(msg);
        }

    if( first_colon_idx != last_colon_idx )
        {
        // "[2a02:6b8::3]:80"
        if( host_and_port[0] != '[' || host_and_port[last_colon_idx-1] != ']' )
            {
            std::string msg = "invalid hostport format: " + host_and_port;
            throw std::runtime_error(msg);
            }
        host_start_idx++;
        host_end_idx--;
        }

    long port = atol(host_and_port.substr(last_colon_idx+1).c_str());
    if( port < 0 || port > 65535 )
        {
        std::string msg = "invalid port in " + host_and_port;
        throw std::runtime_error(msg);
        }

    return getaddrinfo(
        host_and_port.substr(host_start_idx, host_end_idx-host_start_idx),
        host_and_port.substr(last_colon_idx+1) );
    }

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
    for (::addrinfo* cur = res; cur; cur = cur->ai_next)
        result.push_back( *cur );

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

