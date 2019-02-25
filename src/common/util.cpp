#include "util.h"
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "log.h"
#include "math.h"

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

s32 stringCompare(cstr *a, cstr *b)
{
    s32 result = 0;

    if (a && b)
    {
        while (*a && *b && *a == *b)
        {
            ++a;
            ++b;
        }

        result = *a - *b;
        if (result == 0)
        {
            // NOTE(dparajuli): a and b are equal till min(length(a), length(b))
            if (!*a && *b)
            {
                // NOTE(dparajuli): a is smaller in length, a comes first
                result = -1;
            }
            else if (*a && !*b)
            {
                // NOTE(dparajuli): b is smaller in length, b comes first
                result = 1;
            }
        }
    }

    return result;
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

void stringCopy(String *src, u32 srcOffset, String *dest, u32 destOffset, u32 count)
{
    Assert(count <= dest->size - destOffset - 1);
    Assert(srcOffset <= src->length);

    dest->length = 0;
    for (usize i = 0; i < dest->size - 1; ++i)
    {
        dest->buffer[destOffset + i] = src->buffer[srcOffset + i];
        ++dest->length;
    }

    dest->buffer[dest->length] = '\0';
}

String readEntireFile(MemoryArena *arena, cstr *path)
{
    String string = {};

    FILE *fp = fopen(path, "r");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        u32 size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        TemporaryMemory temporaryMemory = BeginTemporaryMemory(arena);
        string = createString(temporaryMemory.arena, size);

        if (fread(string.buffer, 1, size, fp) != size)
        {
            if (feof(fp))
            {
                LOGE("EOF reached reading %s\n", path);
            }
            else if (ferror(fp))
            {
                LOGE("Error reading %s: %s\n", path, strerror(errno));
            }
            EndTemporaryMemory(temporaryMemory);
            string = {};
        }
        else
        {
            string.length = size;
        }

        fclose(fp);
    }
    else
    {
        LOGE("Unable to open %s\n", path);
    }

    return string;
}

