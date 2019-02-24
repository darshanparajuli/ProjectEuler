#include "mem.h"
#include "log.h"
#include "util.h"

void _initMemoryArena(MemoryArena *arena, usize size, u8 *memory)
{
    arena->size = size;
    arena->base = memory;
    arena->used = 0;
    arena->temporaryCount = 0;
}

void *_memoryArenaPush(MemoryArena *arena, usize size, b32 zeroIt)
{
    Assert((arena->used + size) <= arena->size);
    void *result = arena->base + arena->used;
    arena->used += size;

    if (zeroIt)
    {
        ZeroSize(result, size);
    }

    return result;
}

void _memoryArenaReset(MemoryArena *arena, b32 zeroIt)
{
    if (zeroIt)
    {
        ZeroSize(arena->base, arena->size);
    }
    arena->used = 0;
}

TemporaryMemory _beginTemporaryMemory(MemoryArena *arena)
{
    TemporaryMemory temporaryMemory = {};
    temporaryMemory.arena = arena;
    temporaryMemory.used = arena->used;

    ++arena->temporaryCount;

    return temporaryMemory;
}

void _endTemporaryMemory(TemporaryMemory temporaryMemory)
{
    MemoryArena *arena = temporaryMemory.arena;

    Assert(arena->used >= temporaryMemory.used);
    arena->used = temporaryMemory.used;

    Assert(arena->temporaryCount > 0);
    --arena->temporaryCount;
}
