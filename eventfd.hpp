#pragma once

#include <sys/eventfd.h>

namespace unistd
{

typedef ::eventfd_t eventfd_t;

int eventfd(unsigned int initval, int flags);
void eventfd_read(int fd, eventfd_t *value);
eventfd_t eventfd_read(int fd);
void eventfd_write(int fd, eventfd_t value);

} // namespace unistd

