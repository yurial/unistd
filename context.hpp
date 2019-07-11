#pragma once

#include <utility>
#include <ucontext.h>

namespace unistd
{
using ucontext = ::ucontext_t;

void swapcontext(ucontext& ouc, const ucontext& uc);
void getcontext(ucontext& uc);
void setcontext(const ucontext& uc);

ucontext getcontext();

template<class... Args>
void makecontext(ucontext& uc, void (*func)(), int argc, Args&&... args)
    {
    ::makecontext(&uc, func, argc, args...);
    }

template<class... Args>
ucontext makecontext(const ucontext& uc_link, char* stack, size_t stack_size, void (*func)(), Args&&... args)
    {
    ucontext uc = unistd::getcontext();
    uc.uc_link = const_cast<ucontext*>(&uc_link);
    uc.uc_stack.ss_sp = stack;
    uc.uc_stack.ss_size = stack_size;
    unistd::makecontext(uc, func, sizeof...(Args), args...);
    return uc;
    }


} // namespace unistd

