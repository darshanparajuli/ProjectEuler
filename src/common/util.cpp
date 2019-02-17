#include "util.h"
#include <cstdarg>
#include <cstdio>
#include "log.h"

cstr *_getFileName(cstr *path)
{
    u32 count = stringLength(path);

    for (u32 i = count - 1; i >= 0; --i)
    {
        if (*(path + i) == '/')
        {
            return path + i + 1;
        }
    }

    return path;
}

StringBuffer createStringBuffer(char *buffer, u32 size)
{
    StringBuffer sb = {};

    sb.buffer = buffer;
    sb.size = size;
    sb.used = 0;

    return sb;
}

void stringBufferWrite(StringBuffer *sb, cstr *fmt, ...)
{
    if (sb->used >= sb->size)
    {
        LOGD("StringBuffer is full!\n");
    }
    else
    {
        va_list args;
        va_start(args, fmt);

        u32 available = sb->size - sb->used;
        char *buffer = sb->buffer + sb->used;
        sb->used += vsnprintf(buffer, available, fmt, args);

        va_end(args);
    }
}
