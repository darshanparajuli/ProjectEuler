#ifndef PE_UTIL_H
#define PE_UTIL_H

#include <cstdlib>
#include "log.h"
#include "mem.h"
#include "types.h"

#define MacroConcat(a, b) _MacroConcat(a, b)
#define _MacroConcat(a, b) a##b
#define Stringize(s) #s

#define Assert(expr)                                                           \
    if (!(expr))                                                               \
    {                                                                          \
        LOGE("Assertion failed at %s:%d\n", _getFileName(__FILE__), __LINE__); \
        *(volatile char *) 0 = 0;                                              \
    }
#define InvalidCodePath Assert(!"Invalid code path!")

#define FormatString(s, ...) snprintf(s, ArrayCount(s) - 1, __VA_ARGS__)
#define Die() exit(1)

#define GenListHeader(ListName, Type)           \
    struct MacroConcat(ListName, ListNode)      \
    {                                           \
        Type value;                             \
        MacroConcat(ListName, ListNode) * next; \
        MacroConcat(ListName, ListNode) * prev; \
    };                                          \
    struct MacroConcat(ListName, List)          \
    {                                           \
        MacroConcat(ListName, ListNode) * head; \
        MacroConcat(ListName, ListNode) * tail; \
    };                                          \
    void _appendToList(MemoryArena *memory,     \
                       MacroConcat(ListName, List) * list, Type value);

#define GenListSource(ListName, Type)                                  \
    void _appendToList(MemoryArena *memory,                            \
                       MacroConcat(ListName, List) * list, Type value) \
    {                                                                  \
        MacroConcat(ListName, ListNode) *node =                        \
            PushStruct(memory, MacroConcat(ListName, ListNode));       \
        node->value = value;                                           \
        node->next = 0;                                                \
        node->prev = 0;                                                \
                                                                       \
        if (list->head)                                                \
        {                                                              \
            if (list->tail)                                            \
            {                                                          \
                list->tail->next = node;                               \
                node->prev = list->tail;                               \
            }                                                          \
            else                                                       \
            {                                                          \
                list->head->next = node;                               \
                node->prev = list->head;                               \
            }                                                          \
                                                                       \
            list->tail = node;                                         \
        }                                                              \
        else                                                           \
        {                                                              \
            list->head = node;                                         \
        }                                                              \
    }

#define AppendToList(memory, list, value) _appendToList(memory, list, value)

cstr *_getFileName(cstr *path);

internal inline u32 stringLength(cstr *string)
{
    u32 result = 0;

    if (string)
    {
        while (*string++ != '\0')
        {
            ++result;
        }
    }

    return result;
}

#define ImplSwap(type)                          \
    internal inline void swap(type *a, type *b) \
    {                                           \
        type temp = *a;                         \
        *a = *b;                                \
        *b = temp;                              \
    }

ImplSwap(u8);
ImplSwap(u16);
ImplSwap(u32);
ImplSwap(u64);
ImplSwap(s8);
ImplSwap(s16);
ImplSwap(s32);
ImplSwap(s64);
ImplSwap(f32);
ImplSwap(f64);
ImplSwap(char);

struct StringBuffer
{
    char *string;
    u32 capacity;

    u32 length;

    inline char &operator[](usize index)
    {
        return string[index];
    }
};

StringBuffer createStringBuffer(char *buffer, u32 capacity);
StringBuffer createStringBuffer(MemoryArena *memoryArena, u32 capacity);
void stringBufferFormat(StringBuffer *buffer, cstr *fmt, ...);
void stringBufferReverse(StringBuffer *buffer);
void stringBufferCopy(StringBuffer *src, StringBuffer *dest);

internal inline void stringBufferClear(StringBuffer *sb, b32 overwrite = false)
{
    sb->length = 0;
}

internal inline void stringBufferClearOverwite(StringBuffer *sb)
{
    while (sb->length > 0)
    {
        sb->string[sb->length - 1] = 0;
        --sb->length;
    }
}

internal inline u32 charToU32(char c)
{
    u32 result = c - '0';
    return result;
}

internal inline u64 charToU64(char c)
{
    u64 result = c - '0';
    return result;
}

#endif
