#ifndef PE_PROB18_H
#define PE_PROB18_H

/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

3
7 4
2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route.
However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force,
and requires a clever method! ;o)
*/

inline u32 twoDigitCharToU32(char *c)
{
    return charToU32(c[0]) * 10 + charToU32(c[1]);
}

internal u32 **parseInput(MemoryArena *memoryArena, cstr **input, usize inputSize)
{
    u32 **result = 0;

    u32 total = (inputSize * (inputSize + 1)) / 2;
    result = PushArray(memoryArena, u32 *, total);

    for (u32 i = 0; i < inputSize; ++i)
    {
        u32 len = stringGetLength(input[i]);
        result[i] = PushArray(memoryArena, u32, len);
        for (u32 j = 0; j < len; j += 3)
        {
            u32 value = twoDigitCharToU32((char *) &input[i][j]);
            result[i][j / 3] = value;
        }
    }

    return result;
}

SolveProblemFunc(18)
{
    cstr *input[] = {
        "75",
        "95 64",
        "17 47 82",
        "18 35 87 10",
        "20 04 82 47 65",
        "19 01 23 75 03 34",
        "88 02 77 73 07 63 67",
        "99 65 04 28 06 16 70 92",
        "41 41 26 56 83 40 80 70 33",
        "41 48 72 33 47 32 37 16 94 29",
        "53 71 44 65 25 43 91 52 97 51 14",
        "70 11 33 28 77 73 17 78 39 68 17 57",
        "91 71 52 38 17 14 91 43 58 50 27 29 48",
        "63 66 04 68 89 53 67 30 73 16 69 87 40 31",
        "04 62 98 27 23 09 70 98 73 93 38 53 60 04 23",
    };

    TemporaryMemory temporaryMemory = BeginTemporaryMemory(memoryArena);

    u32 **numbers = parseInput(temporaryMemory.arena, input, ArrayCount(input));
    u32 **maxTable = PushArray(temporaryMemory.arena, u32 *, ArrayCount(input));
    for (u32 i = 0; i < ArrayCount(input); ++i)
    {
        maxTable[i] = PushArray(temporaryMemory.arena, u32, i + 1);
    }

    maxTable[0][0] = numbers[0][0];

    for (u32 y = 1; y < ArrayCount(input); ++y)
    {
        for (u32 x = 0; x <= y; ++x)
        {
            u32 parent;
            if (x == 0 || x == y)
            {
                parent = maxTable[y - 1][mathClamp(x, 0, y - 1)];
            }
            else
            {
                parent = mathMax(maxTable[y - 1][x - 1], maxTable[y - 1][x]);
            }

            maxTable[y][x] += parent + numbers[y][x];
        }
    }

    u32 result = 0;
    for (u32 y = 0; y < ArrayCount(input); ++y)
    {
        for (u32 x = 0; x <= y; ++x)
        {
            result = mathMax(result, maxTable[y][x]);
        }
    }

    EndTemporaryMemory(temporaryMemory);

    WriteSolution("%d", result);
}

#endif
