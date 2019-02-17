#ifndef PE_PROB10_H
#define PE_PROB10_H

/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

SolveProblemFunc(10)
{
    u64 result = 0;

    result += 2;

    for (u32 i = 3; i < 2000000; i += 2)
    {
        if (mathIsPrime(i))
        {
            result += i;
        }
    }

    ProblemWriteOutput("%llu\n", result);
}

#endif
