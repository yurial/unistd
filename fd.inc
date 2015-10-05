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

fd::fd():
    m_fd( -1 )
{
}

fd::fd(const fd& origin):
    fd()
{
if ( -1 != origin.m_fd )
    m_fd = unistd::dup( origin );
}

fd::fd(fd&& origin):
    fd()
{
std::swap( m_fd, origin.m_fd );
}

fd::fd(const int& origin):
    fd()
{
if ( -1 != origin )
    m_fd = unistd::dup( origin );
}

fd::fd(int&& origin):
    fd()
{
std::swap( m_fd, origin );
}

fd::~fd()
{
close();
}

fd fd::operator = (const fd& rvalue)
{
fd( rvalue ).swap( *this );
return *this;
}

fd fd::operator = (const int& rvalue)
{
fd( rvalue ).swap( *this );
return *this;
}

fd fd::operator = (int&& rvalue)
{
fd( std::move( rvalue ) ).swap( *this );
return *this;
}

fd::operator int () const
{
return m_fd;
}

void fd::close()
{
if ( -1 == m_fd )
    return;
int fd_val = m_fd; //to avoid double-throw on unistd::close=exception
m_fd = -1;
unistd::close( fd_val );
}

int fd::close(const std::nothrow_t&)
{
if ( -1 == m_fd )
    return 0;
int ret = ::close( m_fd );
m_fd = -1;
return ret;
}

void fd::swap(fd& val)
{
std::swap( m_fd, val.m_fd );
}

} //namespace unistd

