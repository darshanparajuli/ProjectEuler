#ifndef PE_PROB5_H
#define PE_PROB5_H

/*
2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

internal u32 prob5Answer()
{
    u32 result = 2520;

    for (;;)
    {
        b32 remainder = false;

        for (u32 i = 1; i <= 20; ++i)
        {
            if (result % i != 0)
            {
                remainder = true;
                break;
            }
        }

        if (remainder)
        {
            result += 2520;
        }
        else
        {
            break;
        }
    }

    return result;
}

#endif
