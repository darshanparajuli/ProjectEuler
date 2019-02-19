#ifndef PE_PROB16_H
#define PE_PROB16_H

/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

internal void multiplyBy2(StringBuffer *input, StringBuffer *output)
{
    u32 carry = 0;

    for (s32 i = input->used - 1; i >= 0; --i)
    {
        u32 digit = charToU32(input->string[i]);
        u32 result = digit * 2 + carry;
        u32 d = result % 10;
        carry = result / 10;

        stringBufferFormat(output, "%d", d);
    }

    while (carry != 0)
    {
        u32 d = carry % 10;
        stringBufferFormat(output, "%d", d);

        carry /= 10;
    }

    while (output->used > 0 && output->string[output->used - 1] == '0')
    {
        output->string[output->used - 1] = '\0';
        --output->used;
    }
    stringBufferReverse(output);
}

SolveProblemFunc(16)
{
    StringBuffer input = createStringBuffer(memoryArena, KiloBytes(4));
    StringBuffer output = createStringBuffer(memoryArena, KiloBytes(4));

    stringBufferFormat(&input, "%s", "1");

    for (u32 i = 0; i < 1000; ++i)
    {
        stringBufferClear(&output);

        multiplyBy2(&input, &output);
        stringBufferCopy(&output, &input);
    }

    u64 result = 0;
    for (u32 i = 0; i < output.used; ++i)
    {
        result += charToU32(output[i]);
    }

    LOGD("result: %s\n", output.string);

    ProblemWriteOutput("%d", result);
}

#endif
