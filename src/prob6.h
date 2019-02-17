#ifndef PE_PROB6_H
#define PE_PROB6_H

/*
The sum of the squares of the first ten natural numbers is,

1^2 + 2^2 + ... + 10^2 = 385
The square of the sum of the first ten natural numbers is,

(1 + 2 + ... + 10)^2 = 55^2 = 3025
Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

ProblemFunc(6)
{
    u64 result = 0;

    u64 sumOfSquares = 0;
    u64 sum = 0;

    for (u32 i = 1; i <= 100; ++i)
    {
        sumOfSquares += mathSquare(i);
        sum += i;
    }

    u64 squareOfTheSum = mathSquare(sum);
    result = squareOfTheSum - sumOfSquares;

    ProblemWriteOutput("%llu", result);
}

#endif
