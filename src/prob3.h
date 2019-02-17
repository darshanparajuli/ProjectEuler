#ifndef PE_PROB3_H
#define PE_PROB3_H

/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

SolveProblemFunc(3)
{
    u64 input = 600851475143;

    u64 result = 0;

    u64 sqrtOfInput = (u64) mathSquareRoot((f64) input);
    for (u64 i = 3; i < sqrtOfInput; i += 2)
    {
        // LOGD("i: %d\n", i);
        if (input % i == 0 && mathIsPrime(i))
        {
            result = mathMax(i, result);
        }
    }

    ProblemWriteOutput("%llu", result);
}

#endif
