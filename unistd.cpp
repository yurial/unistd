#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <system_error>

#include <ext/mkstr.hpp>
#include <ext/escape.hpp>
#include "unistd.hpp"

namespace unistd
{

int open(const std::string& fname, int flags)
    {
    int new_fd = ::open( fname.c_str(), flags );
    if ( -1 == new_fd )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "open( '%s' )", ext::escape_posix( fname ).c_str() ) );
    return new_fd;
    }

int openat(int dirfd, const std::string& fname, int flags, mode_t mode)
    {
    int new_fd = ::openat( dirfd, fname.c_str(), flags, mode );
    if ( -1 == new_fd )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "openat( '%s' )", ext::escape_posix( fname ).c_str() ) );
    return new_fd;
    }

size_t read(int fd, void* buf, size_t count)
    {
    ssize_t nread = 0;
    TEMP_FAILURE_RETRY( nread = ::read( fd, buf, count ) );
    if ( -1 == nread )
        throw std::system_error( errno, std::system_category(), "read" );
    return nread;
    }

size_t write(int fd, const void* buf, size_t count)
    {
    ssize_t nwrite = 0;
    TEMP_FAILURE_RETRY( nwrite = ::write( fd, buf, count ) );
    if ( -1 == nwrite )
        throw std::system_error( errno, std::system_category(), "write" );
    return nwrite;
    }

void read(int fd, std::vector<char>& buf)
    {
    size_t nread = unistd::read( fd, buf.data(), buf.size() );
    buf.resize( nread );
    }

size_t write(int fd, const std::vector<char>& buf)
    {
    return write( fd, buf.data(), buf.size() );
    }

void read_all(int fd, void* buf, size_t count)
    {
    size_t nread = 0;
    do
        {
        nread = unistd::read( fd, buf, count );
        reinterpret_cast<char*&>( buf ) += nread;
        count -= nread;
        }
    while ( count > 0 && nread > 0 );
    }

void write_all(int fd, const void* buf, size_t count)
    {
    size_t nwrite = 0;
    do
        {
        nwrite = unistd::write( fd, buf, count );
        reinterpret_cast<const char*&>( buf ) += nwrite;
        count -= nwrite;
        }
    while ( count > 0 );
    }

void read_all(int fd, std::vector<char>& buf)
    {
    unistd::read_all( fd, buf.data(), buf.size() );
    }

void write_all(int fd, const std::vector<char>& buf)
    {
    unistd::write_all( fd, buf.data(), buf.size() );
    }

int dup(int fd)
    {
    int new_fd = ::dup( fd );
    if ( -1 == new_fd )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "dup( %d )", fd ) );
    return new_fd;
    }

void close(int fd)
    {
    int ret = ::close( fd );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "close( %d )", fd ) );
    }

void unlink(const std::string& fname)
    {
    int ret = ::unlink( fname.c_str() );
    if ( -1 == ret )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "unlink( '%s' )", ext::escape_posix( fname ).c_str() ) );
    }

void unlinkat(int dirfd, const std::string& fname, int flags)
    {
    int ret = ::unlinkat( dirfd, fname.c_str(), flags );
    if ( 0 != ret )
        throw std::system_error( errno, std::system_category(), ext::mkstr( "unlinkat( '%s' )", ext::escape_posix( fname ).c_str() ) );
    }

} //namespace unistd

