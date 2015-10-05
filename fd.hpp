#ifndef UNISTD_FD_HPP
#define UNISTD_FD_HPP

#include <new>
#include <utility>

namespace unistd
{

class fd
{
protected:
int         m_fd;

public:
inline          fd();
inline          fd(const fd& origin);
inline          fd(fd&& origin);
inline          fd(const int& origin);
inline          fd(int&& origin);
inline          ~fd(); //to avoid throw, call .close(std::nothrow) manualy before destructing

inline  fd      operator = (const fd& rvalue);
inline  fd      operator = (const int& rvalue);
inline  fd      operator = (int&& rvalue);

inline          operator int () const;

inline  void    close();
inline  int     close(const std::nothrow_t&);
inline  void    swap(fd& val);
};

} //namespace unistd

namespace std
{
template<>
inline void swap(unistd::fd& lvalue, unistd::fd& rvalue);
}

#include "fd.inc"

#endif

