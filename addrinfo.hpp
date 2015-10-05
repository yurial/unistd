#ifndef EXT_ADDRINFO_HPP
#define EXT_ADDRINFO_HPP

#include <netdb.h>
#include <string.h>
#include <string>

namespace unistd
{

struct addrinfo
{
int                 ai_flags;
int                 ai_family;
int                 ai_socktype;
int                 ai_protocol;
socklen_t           ai_addrlen;
sockaddr_storage    ai_addr;
std::string         ai_canonname;

        addrinfo();
template <class addrinfo_t>
inline  addrinfo(const addrinfo_t& ai);
        operator ::addrinfo() const;
}; //addrinfo

template <class addrinfo_t>
addrinfo::addrinfo(const addrinfo_t& ai):
        ai_flags( ai.ai_flags ),
        ai_family( ai.ai_family ),
        ai_socktype( ai.ai_socktype ),
        ai_protocol( ai.ai_protocol ),
        ai_addrlen( ai.ai_addrlen ),
        ai_addr(),
        ai_canonname( ai.ai_canonname? std::string( ai.ai_canonname ) : std::string() )
    {
    memcpy( &ai_addr, ai.ai_addr, ai.ai_addrlen );
    }

} //namespace unistd

namespace ext
{
template <typename O, typename I>
O convert_to(const I& value);

template <>
std::string convert_to(const unistd::addrinfo& addr);
} //namespace ext

#endif

