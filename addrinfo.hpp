#pragma once

#include <netdb.h>
#include <string.h>
#include <string>

namespace unistd {

struct addrinfo
{
int                 ai_flags    = 0;
int                 ai_family   = 0;
int                 ai_socktype = 0;
int                 ai_protocol = 0;
socklen_t           ai_addrlen  = 0;
sockaddr_storage    ai_addr;
std::string         ai_canonname;

std::string         ai_host;
std::string         ai_port;

    inline addrinfo() = default;
    template <class addrinfo_t>
    inline addrinfo(const addrinfo_t& ai);
    operator ::addrinfo() const;
}; // addrinfo


template <class addrinfo_t>
addrinfo::addrinfo(const addrinfo_t& ai):
        ai_flags(ai.ai_flags),
        ai_family(ai.ai_family),
        ai_socktype(ai.ai_socktype),
        ai_protocol(ai.ai_protocol),
        ai_addrlen(ai.ai_addrlen),
        ai_addr(),
        ai_canonname(ai.ai_canonname ? std::string(ai.ai_canonname) : std::string())
    {
    ::memcpy(&ai_addr, ai.ai_addr, ai.ai_addrlen);
    }

struct nameinfo
{
std::string host;
std::string serv;
};

} // namespace unistd

namespace ext
{
template <typename O, typename I>
O convert_to(const I& value);

template <>
std::string convert_to(const unistd::addrinfo& addr);
} // namespace ext

