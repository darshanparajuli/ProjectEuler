#ifndef PE_PROB16_H
#define PE_PROB16_H

/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2^1000?
*/

internal void multiplyBy2(String *input, String *output)
{
    u32 carry = 0;

    for (s32 i = input->length - 1; i >= 0; --i)
    {
        u32 digit = charToU32(input->buffer[i]);
        u32 result = digit * 2 + carry;
        u32 d = result % 10;
        carry = result / 10;

        stringFormat(output, "%d", d);
    }

    while (carry != 0)
    {
        u32 d = carry % 10;
        stringFormat(output, "%d", d);

        carry /= 10;
    }

    while (output->length > 0 && output->buffer[output->length - 1] == '0')
    {
        output->buffer[output->length - 1] = '\0';
        --output->length;
    }
    stringReverse(output);
}

SolveProblemFunc(16)
{
    String input = createString(memoryArena, KiloBytes(4));
    String output = createString(memoryArena, KiloBytes(4));

    stringFormat(&input, "%s", "1");

    for (u32 i = 0; i < 1000; ++i)
    {
        stringClear(&output);

        multiplyBy2(&input, &output);
        stringCopy(&output, &input);
    }

    u64 result = 0;
    for (u32 i = 0; i < output.length; ++i)
    {
        result += charToU32(output[i]);
    }

    ProblemWriteOutput("%d", result);
}

#endif
