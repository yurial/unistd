#pragma once

#include <sys/resource.h>

namespace unistd
{

::rusage getrusage(int who);

} //namspace unistd

