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

String createString(char *buffer, u32 size)
{
    String string = {};

    string.buffer = buffer;
    string.size = size;
    string.length = 0;

    return string;
}

void stringFormat(String *string, cstr *fmt, ...)
{
    if ((s32) string->length >= (s32) string->size - 1)
    {
        LOGE("String buffer is full!\n");
    }
    else
    {
        va_list args;
        va_start(args, fmt);

        u32 available = string->size - string->length;
        char *buffer = string->buffer + string->length;

        s32 writtenCount = vsnprintf(buffer, available, fmt, args);

        va_end(args);

        if (writtenCount >= 0 && (u32) writtenCount < available)
        {
            string->length += writtenCount;
        }
        else
        {
            if (writtenCount < 0)
            {
                LOGE("Error writing string: %d\n", writtenCount);
            }
            else
            {
                LOGE("Insufficient string buffer size (excluding null terminator): size = %d, available = %d, input size = %d\n", string->size - 1, available - 1, writtenCount);
            }
        }
    }
}

void stringReverse(String *string)
{
    u32 n = string->length / 2;
    for (u32 i = 0; i < n; ++i)
    {
        swap(&string->buffer[i], &string->buffer[string->length - i - 1]);
    }
}

void stringCopy(String *src, String *dest)
{
    Assert(dest->length <= src->length);

    for (usize i = 0; i < src->length; ++i)
    {
        dest->buffer[i] = src->buffer[i];
    }

    dest->length = src->length;
}
