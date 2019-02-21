#ifndef PE_PROB9_H
#define PE_PROB9_H

/*
A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

a^2 + b^2 = c^2
For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

There exists exactly one Pythagorean triplet for which a + b + c = 1000.
Find the product abc.
*/

SolveProblemFunc(9)
{
    u32 result = 0;

    for (u32 a = 1; a <= 1000; ++a)
    {
        for (u32 b = 1; b <= 1000; ++b)
        {
            for (u32 c = 1; c <= 1000; ++c)
            {
                if ((mathSquare(a) + mathSquare(b)) == mathSquare(c))
                {
                    if ((a + b + c) == 1000)
                    {
                        result = a * b * c;
                        goto end;
                    }
                }
            }
        }
    }

end:
    WriteSolution("%d", result);
}

#endif
