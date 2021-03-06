#ifndef PE_PROB4_H
#define PE_PROB4_H

/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

internal b32 isPalindrome(u32 n)
{
    b32 result = true;

    u32 digits[6] = {};
    u32 digitCount = countDigits(n);

    for (u32 i = 0; i < digitCount; ++i)
    {
        digits[i] = n % 10;
        n /= 10;
    }

    for (u32 i = 0; i < digitCount / 2; ++i)
    {
        if (digits[i] != digits[digitCount - i - 1])
        {
            result = false;
            break;
        }
    }

    return result;
}

SolveProblemFunc(4)
{
    u32 result = 0;

    for (u32 i = 999; i >= 100; --i)
    {
        for (u32 j = 999; j >= 100; --j)
        {
            u32 temp = i * j;
            if (isPalindrome(temp))
            {
                result = mathMax(result, temp);
            }
        }
    }

    WriteSolution("%d", result);
}

#endif
