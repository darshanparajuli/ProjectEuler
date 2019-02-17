#include "math.h"
#include "log.h"

b32 mathIsPrime(u64 n)
{
    b32 result = true;

    if (mathIsEven(n))
    {
        result = false;
    }
    else
    {
        u64 sqrtRootOfN = (u64) mathSquareRoot((f64) n);
        for (u64 i = 3; i < sqrtRootOfN; i += 2)
        {
            if (n % i == 0)
            {
                result = false;
                break;
            }
        }
    }

    return result;
}
