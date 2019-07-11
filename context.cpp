#include "context.hpp"
#include "internal.hpp"
#include <stdarg.h>
#include <system_error>

namespace unistd
{

void swapcontext(ucontext& ouc, const ucontext& uc)
    {
    const int ret = ::swapcontext(&ouc, &uc);
    if (-1 == ret)
        throw std::system_error(errno, std::system_category(), "swapcontext()");
    }

void getcontext(ucontext& uc)
    {
    const int ret = ::getcontext(&uc);
    if (-1 == ret)
        throw std::system_error(errno, std::system_category(), "getcontext()");
    }

void setcontext(const ucontext& uc)
    {
    const int ret = ::setcontext(&uc);
    if (-1 == ret)
        throw std::system_error(errno, std::system_category(), "setcontext()");
    }

ucontext getcontext()
    {
    ucontext uc;
    unistd::getcontext(uc);
    return uc;
    }

} // namespace unistd

