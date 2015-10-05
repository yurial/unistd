#include <string.h>
#include <system_error>
#include <ext/mkstr.hpp>
#include "addrinfo.hpp"

namespace unistd
{

addrinfo::addrinfo():
        ai_flags(),
        ai_family(),
        ai_socktype(),
        ai_protocol(),
        ai_addrlen(),
        ai_addr(),
        ai_canonname()
    {
    }

addrinfo::operator ::addrinfo() const
    {
    ::addrinfo result;
    bzero( &result, sizeof(result) );
    result.ai_flags = ai_flags;
    result.ai_family = ai_family;
    result.ai_socktype = ai_socktype;
    result.ai_protocol = ai_protocol;
    result.ai_addr = const_cast<sockaddr*>( reinterpret_cast<const sockaddr*>( &ai_addr ) );
    result.ai_addrlen = ai_addrlen;
    result.ai_canonname = const_cast<char*>( ai_canonname.c_str() );
    return result;
    }

} //namespace unistd

namespace ext
{

template <>
std::string convert_to(const unistd::addrinfo& addr)
    {
    char host_buf[NI_MAXHOST];
    char serv_buf[NI_MAXSERV];

    int ret = ::getnameinfo( reinterpret_cast<const sockaddr*>( &addr.ai_addr ), addr.ai_addrlen, host_buf, sizeof(host_buf), serv_buf, sizeof(serv_buf), NI_NUMERICHOST | NI_NUMERICSERV );
    if ( 0 != ret )
        return "invalid address";

    if ( addr.ai_family == AF_INET6 )
        return ext::mkstr( "[%s]:%s", host_buf, serv_buf );

    return ext::mkstr( "%s:%s", host_buf, serv_buf );
    }

} //namespace ext

