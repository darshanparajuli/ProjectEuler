#include "common/log.h"
#include "common/math.h"
#include "common/mem.h"
#include "common/util.h"

#include "prob3.h"
#include "prob4.h"
#include "prob5.h"
#include "prob6.h"
#include "prob7.h"
#include "prob8.h"
#include "prob9.h"
#include "prob10.h"
#include "prob11.h"

#define SolveProblem(n, buffer) _SolveProblem(n, buffer)
#define _SolveProblem(n, buffer) MacroConcat(solveProblem, n)(buffer)

#define PROBLEM_NUMBER 11

int main()
{
    char buffer[256];
    StringBuffer stringBuffer = createStringBuffer(buffer, ArrayCount(buffer));

    SolveProblem(PROBLEM_NUMBER, &stringBuffer);

    LOGI("Problem %d solution: %s\n", PROBLEM_NUMBER, stringBuffer.buffer);

    return 0;
}
