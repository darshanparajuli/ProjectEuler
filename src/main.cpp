#include "common/log.h"
#include "common/math.h"
#include "common/mem.h"
#include "common/util.h"

// clang-format off
#define SolveProblemFunc(n) _SolveProblemFunc(n)
#define _SolveProblemFunc(n) internal void MacroConcat(solveProblem, n)(MemoryArena *memoryArena, String *_output)
#define ProblemWriteOutput(...) stringFormat(_output, __VA_ARGS__)

// clang-format off
#include "prob3.h"
#include "prob4.h"
#include "prob5.h"
#include "prob6.h"
#include "prob7.h"
#include "prob8.h"
#include "prob9.h"
#include "prob10.h"
#include "prob11.h"
#include "prob12.h"
#include "prob13.h"
#include "prob14.h"
#include "prob15.h"
#include "prob16.h"
#include "prob17.h"
#include "prob18.h"
#include "prob19.h"

#include "prob67.h"

#define SolveProblem(n, memoryArena, buffer) _SolveProblem(n, memoryArena, buffer)
#define _SolveProblem(n, memoryArena, buffer) MacroConcat(solveProblem, n)(memoryArena, buffer)

#define PROBLEM_NUMBER 19

int main()
{
    MemoryArena memoryArena = {};
    {
        usize size = MegaBytes(32);
        u8 *memory = (u8 *) malloc(size);
        InitMemoryArena(&memoryArena, size, memory);
    }

    String output = createString(&memoryArena, 256);

    SolveProblem(PROBLEM_NUMBER, &memoryArena, &output);

    LOGI("Problem %d solution: %s\n", PROBLEM_NUMBER, output.buffer);

    free(memoryArena.base);

    return 0;
}
