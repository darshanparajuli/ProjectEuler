#ifndef PE_PROB20_H
#define PE_PROB20_H

/*
n! means n × (n − 1) × ... × 3 × 2 × 1

For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/

internal void multiply(String *a, u32 b, String *result)
{
    u32 carry = 0;
    for (s32 i = a->length - 1; i >= 0; --i)
    {
        u32 aa = charToU32(a->buffer[i]);

        u32 v = aa * b + carry;
        carry = v / 10;

        stringFormat(result, "%d", v % 10);
    }

    while (carry)
    {
        stringFormat(result, "%d", carry % 10);
        carry /= 10;
    }

    stringReverse(result);
}

SolveProblemFunc(20)
{
    u32 result = 0;

    String a = createString(memoryArena, 256);
    String b = createString(memoryArena, 256);

    a += "1";
    for (u64 i = 1; i <= 100; ++i)
    {
        stringClear(&b);
        multiply(&a, i, &b);
        stringCopy(&b, &a);
    }

    for (u32 i = 0; i < b.length; ++i)
    {
        result += charToU32(b[i]);
    }

    WriteSolution("%d", result);
}

#endif
