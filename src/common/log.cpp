#include "log.h"
#include <cstdarg>
#include <cstdio>

void _log(cstr *tag, cstr *colorCode, cstr *format, ...)
{
    va_list args;
    va_start(args, format);

    fprintf(stdout, "%s[%s] ", colorCode, tag);
    vfprintf(stdout, format, args);
    fflush(stdout);

    va_end(args);
}
