#pragma once

#include <sys/signalfd.h>

namespace unistd
{

int signalfd(int fd, const sigset_t* mask, int flags = 0) __attribute__((warn_unused_result));;
int signalfd(const sigset_t* mask, int flags = 0) __attribute__((warn_unused_result));;

int signalfd(int fd, const sigset_t& mask, int flags = 0) __attribute__((warn_unused_result));;
int signalfd(const sigset_t& mask, int flags = 0) __attribute__((warn_unused_result));;

} //namespace unistd

#include "signalfd.inc"

