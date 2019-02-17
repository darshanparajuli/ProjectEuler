#include "common/log.h"
#include "common/util.h"
#include "common/mem.h"

#include "prob3.h"
#include "prob4.h"
#include "prob5.h"
#include "prob6.h"
#include "prob7.h"

#define ProblemAnswer(n, buffer) _ProblemAnswer(n, buffer)
#define _ProblemAnswer(n, buffer) prob##n##Answer(buffer)

#define PROBLEM_NUMBER 7

int main()
{
    char buffer[256];
    StringBuffer stringBuffer = createStringBuffer(buffer, ArrayCount(buffer));

    ProblemAnswer(PROBLEM_NUMBER, &stringBuffer);

    LOGI("problem %d answer: %s\n", PROBLEM_NUMBER, stringBuffer.buffer);

    return 0;
}
