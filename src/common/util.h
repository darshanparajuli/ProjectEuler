#ifndef PE_UTIL_H
#define PE_UTIL_H

#include <cstdlib>
#include "log.h"
#include "types.h"

#define MacroConcat(a, b) _MacroConcat(a, b)
#define _MacroConcat(a, b) a##b
#define Stringize(s) #s

#define ProblemFunc(n) _ProblemFunc(n)
#define _ProblemFunc(n) internal void prob##n##Answer(StringBuffer *output)
#define ProblemWriteOutput(...) stringBufferWrite(output, __VA_ARGS__)

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

#define SwapImpl(type)                          \
    internal inline void swap(type *a, type *b) \
    {                                           \
        type temp = *a;                         \
        *a = *b;                                \
        *b = temp;                              \
    }

SwapImpl(u8);
SwapImpl(u16);
SwapImpl(u32);
SwapImpl(u64);
SwapImpl(s8);
SwapImpl(s16);
SwapImpl(s32);
SwapImpl(s64);
SwapImpl(f32);
SwapImpl(f64);

struct StringBuffer
{
    char *buffer;
    u32 size;

    u32 used;
};

StringBuffer createStringBuffer(char *buffer, u32 size);
void stringBufferWrite(StringBuffer *buffer, cstr *fmt, ...);

#endif
