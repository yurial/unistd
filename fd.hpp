#pragma once

#include <new>
#include <utility>

namespace unistd
{

// this class implements RAII for unix file descriptors
class fd
{
public:
typedef int native_type;
enum: native_type
    {
    bad_fileno = -1
    };

inline      fd() noexcept;
inline      fd(fd&& origin) noexcept;
inline      fd(const fd& origin);
inline      ~fd() noexcept; // std::terminate() at throw

inline bool operator==(const fd& rvalue) const = delete;

inline fd&  operator=(fd&& rvalue);
inline fd&  operator=(const fd& rvalue);
inline      operator native_type() const noexcept;

inline void close();
inline int  close(const std::nothrow_t&) noexcept; // return errcode instead of throwing exception
inline void swap(fd& val) noexcept;

inline static fd dup(native_type val);            // construct unistd::fd using ::dup(val)
inline static fd nodup(native_type val) noexcept; // construct unistd::fd without call ::dup(val)

protected:
native_type m_fd;
};

} // namespace unistd

namespace std
{
template <>
inline void swap(unistd::fd& lvalue, unistd::fd& rvalue);
}

#include "fd.inc"

