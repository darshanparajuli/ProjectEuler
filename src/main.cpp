#include "common/log.h"
#include "common/util.h"

#include "prob3.h"
#include "prob4.h"
#include "prob5.h"
#include "prob6.h"

#define ProblemAnswer(n) _ProblemAnswer(n)
#define _ProblemAnswer(n) prob##n##Answer()

#define PROBLEM_NUMBER 6

int main()
{
    LOGI("problem %d answer: %llu\n", PROBLEM_NUMBER, ProblemAnswer(PROBLEM_NUMBER));

    return 0;
}
