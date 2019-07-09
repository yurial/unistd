#include "addrinfo.hpp"
#include "internal.hpp"
#include <system_error>

namespace unistd
{
nameinfo getnameinfo(const addrinfo& addr); // fwd

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

} // namespace unistd

namespace ext
{

template <>
std::string convert_to(const unistd::addrinfo& addr)
    {
    const unistd::nameinfo& info = unistd::getnameinfo(addr);

    if (addr.ai_family == AF_INET6)
        return unistd::internal::mkstr("[%s]:%s", info.host.c_str(), info.serv.c_str());
    else
        return unistd::internal::mkstr("%s:%s", info.host.c_str(), info.serv.c_str());
    }

} // namespace ext
