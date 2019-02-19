#include "common/log.h"
#include "common/math.h"
#include "common/mem.h"
#include "common/util.h"

#define SolveProblemFunc(n) _SolveProblemFunc(n)
#define _SolveProblemFunc(n) internal void MacroConcat(solveProblem, n)(MemoryArena * memoryArena, StringBuffer * _output)
#define ProblemWriteOutput(...) stringBufferFormat(_output, __VA_ARGS__)

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

#define SolveProblem(n, memoryArena, buffer) _SolveProblem(n, memoryArena, buffer)
#define _SolveProblem(n, memoryArena, buffer) MacroConcat(solveProblem, n)(memoryArena, buffer)

#define PROBLEM_NUMBER 16

int main()
{
    MemoryArena memoryArena = {};
    {
        usize size = MegaBytes(32);
        u8 *memory = (u8 *) malloc(size);
        InitMemoryArena(&memoryArena, size, memory);
    }

    StringBuffer stringBuffer = createStringBuffer(&memoryArena, 256);

    SolveProblem(PROBLEM_NUMBER, &memoryArena, &stringBuffer);

    LOGI("Problem %d solution: %s\n", PROBLEM_NUMBER, stringBuffer.string);

    free(memoryArena.base);

    return 0;
}
