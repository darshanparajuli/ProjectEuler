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

    sb.string = buffer;
    sb.size = size;
    sb.used = 0;

    return sb;
}

StringBuffer createStringBuffer(MemoryArena *memoryArena, u32 size)
{
    char *buffer = PushArray(memoryArena, char, size);
    return createStringBuffer(buffer, size);
}

void stringBufferFormat(StringBuffer *sb, cstr *fmt, ...)
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
        char *buffer = sb->string + sb->used;
        sb->used += vsnprintf(buffer, available, fmt, args);

        va_end(args);
    }
}

void stringBufferReverse(StringBuffer *buffer)
{
    u32 n = buffer->used / 2;
    for (u32 i = 0; i < n; ++i)
    {
        swap(&buffer->string[i], &buffer->string[buffer->used - i - 1]);
    }
}


void stringBufferCopy(StringBuffer *src, StringBuffer *dest)
{
    Assert(dest->used <= src->used);

    for (usize i = 0; i < src->used; ++i)
    {
        dest->string[i] = src->string[i];
    }

    dest->used = src->used;
}
