#include "internal.hpp"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

namespace unistd
{
namespace internal
{

std::string escape_posix(const std::string& str)
    {
    std::string result = str;
    size_t pos = 0;
    for (;;) {
        static char symbols[] = "\a\b\t\n\v\f\r\0";
        pos = result.find_first_of(symbols, pos, sizeof(symbols));
        if (pos == std::string::npos)
            break;
        std::string replacement;
        switch (result[pos]) {
            case '\0':
                replacement = "\\0";
                break;
            case '\a':
                replacement = "\\a";
                break;
            case '\b':
                replacement = "\\b";
                break;
            case '\n':
                replacement = "\\n";
                break;
            case '\t':
                replacement = "\\t";
                break;
            case '\v':
                replacement = "\\v";
                break;
            case '\f':
                replacement = "\\f";
                break;
            case '\r':
                replacement = "\\r";
                break;
        }
        result.replace(pos, 1, replacement);
        pos += replacement.size();
    };
    return result;
    }

std::string escape_html(const std::string& str)
    {
    return escape_posix(escape<std::string>(str, "\\/\'\""));
    }

std::string mkstr(const char* fmt, ...)
    {
    char* str = NULL;
    int size = 0;

    va_list ap;
    va_start(ap, fmt);
    size = ::vasprintf(&str, fmt, ap);
    va_end(ap);

    if (-1 == size) // vasnprintf fail if memory allocation failed
        throw std::bad_alloc();

    const std::string result(str, size);
    ::free(str);
    return result;
    }

} // namespace internal
} // namespace unistd

