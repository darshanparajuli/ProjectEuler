#ifndef PE_PROB3_H
#define PE_PROB3_H

#include "common/math.h"

/*

The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?

*/

internal u64 prob3LargestPrimeFactor()
{
    u64 input = 600851475143;

    u64 result = 0;

    s64 start = (s64)((f64) input / 256.0) + 1;
    // LOGD("start: %ld\n", start);

    for (s64 i = start; i >= 3; i -= 2)
    {
        // LOGD("i: %d\n", i);
        if (input % i == 0 && mathIsPrime((u64) i))
        {
            result = i;
            break;
        }
    }

    return result;
}

#endif
