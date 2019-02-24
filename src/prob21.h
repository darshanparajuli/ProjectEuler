#ifndef PE_PROB21_H
#define PE_PROB21_H

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
