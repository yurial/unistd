#include "unistd.hpp"
#include "internal.hpp"
#include "compat.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <system_error>

namespace unistd
{

int open(const std::string& fname, int flags)
    {
    const int new_fd = ::open(fname.c_str(), flags);
    if (-1 == new_fd)
        throw std::system_error(errno, std::system_category(), internal::mkstr("open( '%s' )", internal::escape_posix(fname).c_str()));
    return new_fd;
    }

int openat(int dirfd, const std::string& fname, int flags, mode_t mode)
    {
    const int new_fd = ::openat(dirfd, fname.c_str(), flags, mode);
    if (-1 == new_fd)
        throw std::system_error(errno, std::system_category(), internal::mkstr("openat( '%s' )", internal::escape_posix(fname).c_str()));
    return new_fd;
    }

size_t read(int fd, void* buf, size_t count)
    {
    ssize_t nread = 0;
    TEMP_FAILURE_RETRY(nread = ::read(fd, buf, count));
    if (-1 == nread)
        throw std::system_error(errno, std::system_category(), "read");
    return nread;
    }

size_t write(int fd, const void* buf, size_t count)
    {
    ssize_t nwrite = 0;
    TEMP_FAILURE_RETRY(nwrite = ::write(fd, buf, count));
    if (-1 == nwrite)
        throw std::system_error(errno, std::system_category(), "write");
    return nwrite;
    }

void read(int fd, std::vector<char>& buf)
    {
    const size_t nread = unistd::read(fd, buf.data(), buf.size());
    buf.resize(nread);
    }

size_t write(int fd, const std::vector<char>& buf)
    {
    return write(fd, buf.data(), buf.size());
    }

void read_all(int fd, void* buf, size_t count)
    {
    size_t nread = 0;
    do
        {
        nread = unistd::read(fd, buf, count);
        reinterpret_cast<char*&>(buf) += nread;
        count -= nread;
        }
    while (count > 0 && nread > 0);
    }

void write_all(int fd, const void* buf, size_t count)
    {
    size_t nwrite = 0;
    do
        {
        nwrite = unistd::write(fd, buf, count);
        reinterpret_cast<const char*&>(buf) += nwrite;
        count -= nwrite;
        }
    while (count > 0);
    }

void read_all(int fd, std::vector<char>& buf)
    {
    unistd::read_all(fd, buf.data(), buf.size());
    }

void write_all(int fd, const std::vector<char>& buf)
    {
    unistd::write_all(fd, buf.data(), buf.size());
    }

int dup(int fd)
    {
    const int new_fd = ::dup(fd);
    if (-1 == new_fd)
        throw std::system_error(errno, std::system_category(), internal::mkstr("dup( %d )", fd));
    return new_fd;
    }

void close(int fd)
    {
    const int ret = ::close(fd);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), internal::mkstr("close( %d )", fd));
    }

void unlink(const std::string& fname)
    {
    const int ret = ::unlink(fname.c_str());
    if (-1 == ret)
        throw std::system_error(errno, std::system_category(), internal::mkstr("unlink( '%s' )", internal::escape_posix(fname).c_str()));
    }

void unlinkat(int dirfd, const std::string& fname, int flags)
    {
    const int ret = ::unlinkat(dirfd, fname.c_str(), flags);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), internal::mkstr("unlinkat( '%s' )", internal::escape_posix(fname).c_str()));
    }

void renameat(int olddirfd, const std::string& oldpath, int newdirfd, const std::string& newpath)
    {
    const int ret = ::renameat(olddirfd, oldpath.c_str(), newdirfd, newpath.c_str());
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), internal::mkstr("renameat( '%s', '%s' )", internal::escape_posix(oldpath).c_str(), internal::escape_posix(newpath).c_str()));
    }

void linkat(int olddirfd, const std::string& oldpath, int newdirfd, const std::string& newpath, int flags)
    {
    const int ret = ::linkat(olddirfd, oldpath.c_str(), newdirfd, newpath.c_str(), flags);
    if (0 != ret)
        throw std::system_error( errno, std::system_category(), internal::mkstr("linkat( '%s', '%s' )", internal::escape_posix(oldpath).c_str(), internal::escape_posix(newpath).c_str()));
    }

bool flock(int fd, int operation)
    {
    const int ret = ::flock(fd, operation);
    if (0 != ret)
        {
        if (EWOULDBLOCK == errno)
            return false;
        throw std::system_error(errno, std::system_category(), internal::mkstr("flock( %d )", fd));
        }
    return true;
    }

stat fstat(int fd)
    {
    stat result;
    memset(&result, 0, sizeof(result));
    int ret = fstat(fd, &result);
    if (0 != ret)
        throw std::system_error(errno, std::system_category(), internal::mkstr("fstat( %d )", fd));
    return result;
    }

void mkdir(const std::string& pathname, mode_t mode)
    {
    const int ret = ::mkdir(pathname.c_str(), mode);
    if (0 != ret)
        {
        throw std::system_error(errno, std::system_category(), internal::mkstr("mkdir( %s )", pathname.c_str()));
        }
    }

void* mmap(void* addr, size_t len, int prot, int flags, int fd, off_t offset)
    {
    void* const pointer = ::mmap (addr, len, prot, flags, fd, offset);
    if (pointer == MAP_FAILED)
        {
        throw std::system_error(errno, std::system_category(), "mmap(...) failed");
        }
    return pointer;
    }

} // namespace unistd

