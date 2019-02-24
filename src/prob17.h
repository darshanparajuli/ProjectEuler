#ifndef PE_PROB17_H
#define PE_PROB17_H

/*
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?


NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and
      115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
*/

internal void writeNumber(cstr **table, u32 n, String *output)
{
    if (n == 1000)
    {
        stringFormat(output, "one thousand");
    }
    else
    {
        if (n >= 100)
        {
            u32 d = n / 100;
            stringFormat(output, "%s hundred", table[(d - 1)]);
            n %= 100;

            if (n > 0)
            {
                stringFormat(output, " and ");
            }
        }

        if (n >= 1 && n <= 20)
        {
            stringFormat(output, "%s", table[n - 1]);
        }
        else if (n >= 21 && n < 100)
        {
            u32 d = n % 10;
            u32 d2 = n / 10;

            stringFormat(output, "%s", table[19 + (d2 - 2)]);

            if (d != 0)
            {
                stringFormat(output, "-%s", table[d - 1]);
            }
        }
    }
}

inline u32 count(String *string)
{
    u32 result = 0;

    for (u32 i = 0; i < string->length; ++i)
    {
        switch (string->buffer[i])
        {
            case ' ':
            case '-':
            {
                // NOTE(dparajuli): skip
            }
            break;

            default:
            {
                ++result;
            }
            break;
        }
    }

    return result;
}

SolveProblemFunc(17)
{
    cstr *table[] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",

        // [9]
        "ten",
        "eleven",
        "twelve",
        "thirteen",
        "fourteen",
        "fifteen",
        "sixteen",
        "seventeen",
        "eighteen",
        "nineteen",

        // [19]
        "twenty",
        "thirty",
        "forty",
        "fifty",
        "sixty",
        "seventy",
        "eighty",
        "ninety",
    };

    String string = createString(memoryArena, KiloBytes(4));

    b32 result = 0;

    for (u32 i = 1; i <= 1000; ++i)
    {
        stringClear(&string);
        writeNumber(table, i, &string);

        // LOGD("%s\n", buffer.string);

        result += count(&string);
    }

    WriteSolution("%d", result);
}

#endif
