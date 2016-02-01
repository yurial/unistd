#ifndef UNISTD_FD_HPP
#define UNISTD_FD_HPP

#include <new>
#include <utility>

namespace unistd
{

//this class implements RAII for unix file descriptors
class fd
{
protected:
int             m_fd;

public:
enum { bad_fileno = -1 };

inline          fd() noexcept;
inline          fd(fd&& origin) noexcept;
inline          fd(const fd& origin);
inline          ~fd() noexcept; //std::terminate() at throw

inline  bool    operator == (const fd& rvalue) const = delete;

inline  fd&     operator = (fd&& rvalue);
inline  fd&     operator = (const fd& rvalue);
inline          operator int () const noexcept;

inline  void    close();
inline  int     close(const std::nothrow_t&) noexcept; //return errcode instead of throwing exception
inline  void    swap(fd& val) noexcept;

inline static   fd dup(int val);            //construct unistd::fd using ::dup(val)
inline static   fd nodup(int val) noexcept; //construct unistd::fd without call ::dup(val)
};

} //namespace unistd

namespace std
{
template<>
inline void swap(unistd::fd& lvalue, unistd::fd& rvalue);
}

#include "fd.inc"

#endif

