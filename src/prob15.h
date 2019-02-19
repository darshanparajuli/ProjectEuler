#ifndef PE_PROB15_H
#define PE_PROB15_H

/*
Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down,
there are exactly 6 routes to the bottom right corner.

How many such routes are there through a 20×20 grid?
*/

SolveProblemFunc(15)
{
    u64 result = 0;

    u32 total = 20;

    u64 waysToGetToOuterPoints[32] = {};
    waysToGetToOuterPoints[0] = 1;

    for (u32 i = 1; i <= total; ++i)
    {
        result = 0;
        for (u32 k = 0; k < i; ++k)
        {
            result += 2 * waysToGetToOuterPoints[k];
        }

        for (u32 k = 1; k < i; ++k)
        {
            waysToGetToOuterPoints[k] += waysToGetToOuterPoints[k - 1];
        }
        waysToGetToOuterPoints[i] = result;
    }

    ProblemWriteOutput("%llu", result);
}

#endif
