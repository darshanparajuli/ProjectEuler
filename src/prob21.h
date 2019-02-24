#ifndef PE_PROB21_H
#define PE_PROB21_H

/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

SolveProblemFunc(21)
{
    u32 result = 0;

    for (u32 i = 2; i <= 10000; ++i)
    {
        TemporaryMemory temporaryMemory = BeginTemporaryMemory(memoryArena);

        u32 *divisors1 = PushArray(temporaryMemory.arena, u32, 10000);
        u32 divisors1Count = 0;

        u32 n1 = i / 2;
        for (u32 j = 1; j <= n1; ++j)
        {
            if (i % j == 0)
            {
                divisors1[divisors1Count++] = j;
            }
        }

        u32 sum1 = 0;
        for (u32 j = 0; j < divisors1Count; ++j)
        {
            sum1 += divisors1[j];
        }

        u32 *divisors2 = PushArray(temporaryMemory.arena, u32, 10000);
        u32 divisors2Count = 0;

        u32 n2 = sum1 / 2;
        for (u32 j = 1; j <= n2; ++j)
        {
            if (sum1 % j == 0)
            {
                divisors2[divisors2Count++] = j;
            }
        }

        u32 sum2 = 0;
        for (u32 j = 0; j < divisors2Count; ++j)
        {
            sum2 += divisors2[j];
        }

        if (i == sum2 && sum1 != sum2)
        {
            result += sum1;
        }

        EndTemporaryMemory(temporaryMemory);
    }

    WriteSolution("%d", result);
}

#endif
