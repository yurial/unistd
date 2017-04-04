#ifndef UNISTD_UNISTD_HPP
#define UNISTD_UNISTD_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <vector>
#include <string>

//all unistd::* functions is a stndard glibc functions that throw std::system_error/std::runtime_error on error
//some of standard functions has advanced easy-to-use overloadings (ex: write(std::vector) )

namespace unistd
{
typedef struct ::stat stat;

int     open(const std::string& fname, int flags) __attribute__((warn_unused_result));
int     openat(int dirfd, const std::string& fname, int flags, mode_t mode) __attribute__((warn_unused_result));
int     dup(int fd) __attribute__((warn_unused_result));
void    close(int fd);
void    unlink(const std::string& fname);
void    unlinkat(int dirfd, const std::string& fname, int flags = 0);
void    renameat(int olddirfd, const std::string& oldpath, int newdirfd, const std::string& newpath);
void    linkat(int olddirfd, const std::string& oldpath, int newdirfd, const std::string& newpath, int flags = 0);
bool    flock(int fd, int operation);


size_t  read(int fd, void* buf, size_t count) __attribute__((warn_unused_result));
size_t  write(int fd, const void* buf, size_t count) __attribute__((warn_unused_result));
void    read(int fd, std::vector<char>& buf);
size_t  write(int fd, const std::vector<char>& buf) __attribute__((warn_unused_result));

void    read_all(int fd, void* buf, size_t count);
void    write_all(int fd, const void* buf, size_t count);
void    read_all(int fd, std::vector<char>& buf);
void    write_all(int fd, const std::vector<char>& buf);

stat    fstat(int fd);

void    mkdir(const std::string& pathname, mode_t mode = 0775);
} //namespace unistd

#endif

