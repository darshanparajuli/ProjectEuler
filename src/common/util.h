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

inline u32 stringGetLength(cstr *string)
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

#define ImplSwap(type)                 \
    inline void swap(type *a, type *b) \
    {                                  \
        type temp = *a;                \
        *a = *b;                       \
        *b = temp;                     \
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

struct String
{
    char *buffer;
    u32 size;

    u32 length;

    inline char &operator[](usize index)
    {
        return buffer[index];
    }
};

ImplSwap(String *);

String createString(char *buffer, u32 size);

inline String createString(MemoryArena *memoryArena, u32 size)
{
    size += 1;  // for null termination
    char *buffer = PushArray(memoryArena, char, size);
    return createString(buffer, size);
}

void stringFormat(String *string, cstr *fmt, ...);
void stringReverse(String *string);
void stringCopy(String *src, String *dest);

inline String &operator+=(String &string, cstr *s)
{
    stringFormat(&string, "%s", s);
    return string;
}

inline void stringClear(String *string)
{
    string->length = 0;
    string->buffer[0] = 0;
}

inline u32 charToU32(char c)
{
    u32 result = c - '0';
    return result;
}

inline u64 charToU64(char c)
{
    u64 result = c - '0';
    return result;
}

inline b32 isDigit(char c)
{
    return c >= '0' && c <= '9';
}

#endif
