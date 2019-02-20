#include "util.h"
#include <cstdarg>
#include <cstdio>
#include "log.h"

cstr *_getFileName(cstr *path)
{
    u32 count = stringGetLength(path);

    for (u32 i = count - 1; i >= 0; --i)
    {
        if (*(path + i) == '/')
        {
            return path + i + 1;
        }
    }

    return path;
}

StringBuffer createStringBuffer(char *buffer, u32 capacity)
{
    StringBuffer sb = {};

    sb.string = buffer;
    sb.capacity = capacity;
    sb.length = 0;

    return sb;
}

StringBuffer createStringBuffer(MemoryArena *memoryArena, u32 capacity)
{
    char *buffer = PushArray(memoryArena, char, capacity);
    return createStringBuffer(buffer, capacity);
}

void stringBufferFormat(StringBuffer *sb, cstr *fmt, ...)
{
    if (sb->length >= sb->capacity)
    {
        LOGD("StringBuffer is full!\n");
    }
    else
    {
        va_list args;
        va_start(args, fmt);

        u32 available = sb->capacity - sb->length;
        char *buffer = sb->string + sb->length;
        sb->length += vsnprintf(buffer, available, fmt, args);

        va_end(args);
    }
}

void stringBufferReverse(StringBuffer *buffer)
{
    u32 n = buffer->length / 2;
    for (u32 i = 0; i < n; ++i)
    {
        swap(&buffer->string[i], &buffer->string[buffer->length - i - 1]);
    }
}


void stringBufferCopy(StringBuffer *src, StringBuffer *dest)
{
    Assert(dest->length <= src->length);

    for (usize i = 0; i < src->length; ++i)
    {
        dest->string[i] = src->string[i];
    }

    dest->length = src->length;
}
