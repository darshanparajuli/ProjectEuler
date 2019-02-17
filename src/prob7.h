#ifndef PE_PROB7_H
#define PE_PROB7_H

/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10_001st prime number?
*/

ProblemFunc(7)
{
    u32 count = 10001;

    u32 result = 0;

    u32 primeCount = 0;

    for (u32 n = 1;; n += 2)
    {
        if (mathIsPrime(n))
        {
            ++primeCount;
            if ((primeCount + 1) == count)
            {
                result = n;
                break;
            }
        }
    }

    ProblemWriteOutput("%d", result);
}

#endif
