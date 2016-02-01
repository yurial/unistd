#include <unistd.h>
#include "unistd.hpp"

namespace std
{
template<>
void swap(unistd::fd& lvalue, unistd::fd& rvalue)
    {
    lvalue.swap( rvalue );
    }

} //namespace std

namespace unistd
{

fd::fd() noexcept:
        m_fd( fd::bad_fileno )
    {
    }

fd::fd(fd&& origin) noexcept:
        fd()
    {
    std::swap( m_fd, origin.m_fd );
    }

fd::fd(const fd& origin):
        fd()
    {
    if ( fd::bad_fileno != origin )
        m_fd = unistd::dup( origin.m_fd );
    }

fd::~fd() noexcept
    {
    close();
    }

fd& fd::operator = (fd&& rvalue)
    {
    fd( std::move( rvalue ) ).swap( *this );
    return *this;
    }

fd& fd::operator = (const fd& rvalue)
    {
    fd( rvalue ).swap( *this );
    return *this;
    }

fd::operator int () const noexcept
    {
    return m_fd;
    }

void fd::close()
    {
    if ( fd::bad_fileno == m_fd )
        return;
    int fd_val = m_fd; //to avoid double-throw on unistd::close=exception
    m_fd = fd::bad_fileno;
    unistd::close( fd_val );
    }

int fd::close(const std::nothrow_t&) noexcept
    {
    if ( fd::bad_fileno == m_fd )
        return 0;
    int ret = ::close( m_fd );
    m_fd = fd::bad_fileno;
    return ret;
    }

void fd::swap(fd& val) noexcept
    {
    std::swap( m_fd, val.m_fd );
    }

fd fd::dup(int val)
    {
    fd result;
    if ( fd::bad_fileno != val )
        result.m_fd = unistd::dup( val );
    return result;
    }

fd fd::nodup(int val) noexcept
    {
    fd result;
    result.m_fd = val;
    return result;
    }

} //namespace unistd

