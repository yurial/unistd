#pragma once

#if __cplusplus > 199711L
#define __NO_EXCEPT_DECL__ noexcept(true)
#else
#define __NO_EXCEPT_DECL__
#endif

#ifndef TEMP_FAILURE_RETRY
#define TEMP_FAILURE_RETRY(expr)                                                                                       \
    ({                                                                                                                 \
        long int _res;                                                                                                 \
        do                                                                                                             \
            _res = (long int)(expr);                                                                                   \
        while (_res == -1L && errno == EINTR);                                                                         \
        _res;                                                                                                          \
    })
#endif
