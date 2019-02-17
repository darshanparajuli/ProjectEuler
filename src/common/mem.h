#ifndef PE_MEM_H
#define PE_MEM_H

#include "types.h"

#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))
#define ZeroSize(ptr, size) _zeroIt(ptr, size)
#define ZeroStruct(s) _zeroIt(&(s), sizeof(s))
#define ZeroArray(ptr, count) _zeroIt(ptr, (count) * sizeof((ptr)[0]))

#define InitMemoryArena(arena, size, memory) _initMemoryArena(arena, (usize)(size), memory)
#define PushStruct(arena, type) ((type *) _memoryArenaPush(arena, sizeof(type)))
#define PushArray(arena, type, count) ((type *) _memoryArenaPush(arena, sizeof(type) * (usize)(count)))
#define ResetMemoryArena(arena) _memoryArenaReset(arena, false)
#define ZeroMemoryArena(arena) _memoryArenaReset(arena, true)

#define BeginTemporaryMemory(arena) _beginTemporaryMemory(arena)
#define EndTemporaryMemory(temporaryMemory) _endTemporaryMemory(temporaryMemory)

struct MemoryArena
{
    u8 *base;
    usize size;

    usize used;
    s32 temporaryCount;
};

struct GameMemory
{
    MemoryArena permanent;
    MemoryArena transient;
};

void _initMemoryArena(MemoryArena *arena, usize size, u8 *memory);
void *_memoryArenaPush(MemoryArena *mem, usize size);
void _memoryArenaReset(MemoryArena *mem, b32 zeroIt);

struct TemporaryMemory
{
    MemoryArena *arena;
    usize used;
};

TemporaryMemory _beginTemporaryMemory(MemoryArena *arena);
void _endTemporaryMemory(TemporaryMemory memoryArena);

inline void _zeroIt(void *ptr, usize size)
{
    u8 *byte = (u8 *) ptr;
    while (size--)
    {
        *byte++ = 0;
    }
}

#endif
