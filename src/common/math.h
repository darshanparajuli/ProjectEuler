#ifndef PE_MATH_H
#define PE_MATH_H

#include <math.h>
#include <climits>
#include "types.h"

#define KiloBytes(a) ((a) * (u64) 1024)
#define MegaBytes(a) (KiloBytes(a) * (u64) 1024)
#define GigaBytes(a) (MegaBytes(a) * (u64) 1024)

#define MATH_PI 3.14159265358979323846f
#define MATH_2PI (2.0f * MATH_PI)

struct RngState
{
    u32 state;
};

internal inline u32 randomU32(RngState *state)
{
    /* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
    u32 x = state->state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state->state = x;
    return x;
}

internal inline f32 mathRandomF32(RngState *state)
{
    return (f32) randomU32(state) / (f32) UINT_MAX;
}

internal inline f32 mathRandomF32InRange(RngState *state, f32 min, f32 max)
{
    return min + (max - min) * mathRandomF32(state);
}

internal inline u32 mathRandomU32InRange(RngState *state, u32 min, u32 max)
{
    return min + (u32)((max - min) * mathRandomF32(state));
}

internal inline f32 mathSquareRoot(f32 n)
{
    return sqrtf(n);
}

internal inline f64 mathSquareRoot(f64 n)
{
    return sqrt(n);
}

#define ImplMathSquare(type)                \
    internal inline type mathSquare(type n) \
    {                                       \
        return n * n;                       \
    }

ImplMathSquare(f32);
ImplMathSquare(f64);
ImplMathSquare(u8);
ImplMathSquare(u16);
ImplMathSquare(u32);
ImplMathSquare(u64);
ImplMathSquare(s8);
ImplMathSquare(s16);
ImplMathSquare(s32);
ImplMathSquare(s64);

internal inline f32 mathSin(f32 n)
{
    return sinf(n);
}

internal inline f32 mathCos(f32 n)
{
    return cosf(n);
}

internal inline f32 mathTan(f32 n)
{
    return tanf(n);
}

internal inline f32 mathAtan2(f32 y, f32 x)
{
    return atan2f(y, x);
}

internal inline f32 mathFloor(f32 n)
{
    return floorf(n);
}

internal inline f32 mathCeil(f32 n)
{
    return ceilf(n);
}

internal inline f32 mathClamp(f32 value, f32 min, f32 max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

internal inline u32 mathClamp(u32 value, u32 min, u32 max)
{
    return (value < min) ? min : ((value > max) ? max : value);
}

internal inline f32 mathClamp01(f32 value)
{
    return mathClamp(value, 0.0f, 1.0f);
}

internal inline f32 mathMap(f32 value, f32 fromMin, f32 fromMax, f32 toMin, f32 toMax)
{
    return toMin + (value / (fromMax - fromMin)) * (toMax - toMin);
}

internal inline f32 mathLerp(f32 start, f32 end, f32 t)
{
    return (1.0f - t) * start + t * end;
}

internal inline f32 mathExp(f32 n)
{
    return exp(n);
}

internal inline f32 mathExp2(f32 n)
{
    return exp2(n);
}

internal inline f32 mathAbs(f32 n)
{
    return (n >= 0.0f) ? n : -n;
}

#define ImplMathMin(type)                        \
    internal inline type mathMin(type a, type b) \
    {                                            \
        return a < b ? a : b;                    \
    }

ImplMathMin(u8);
ImplMathMin(u16);
ImplMathMin(u32);
ImplMathMin(u64);

ImplMathMin(s8);
ImplMathMin(s16);
ImplMathMin(s32);
ImplMathMin(s64);

ImplMathMin(f32);
ImplMathMin(f64);

#define ImplMathMax(type)                        \
    internal inline type mathMax(type a, type b) \
    {                                            \
        return a > b ? a : b;                    \
    }

ImplMathMax(u8);
ImplMathMax(u16);
ImplMathMax(u32);
ImplMathMax(u64);

ImplMathMax(s8);
ImplMathMax(s16);
ImplMathMax(s32);
ImplMathMax(s64);

ImplMathMax(f32);
ImplMathMax(f64);

internal inline u32 mathRoundUpToPowerOfTwo(u32 value)
{
    --value;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    ++value;

    return value;
}

internal inline f32 easeOutCubic(f32 time, f32 start, f32 change, f32 duration)
{
    time /= duration;
    --time;
    return change * (time * time * time + 1) + start;
}

internal inline f32 easeInOutCubic(f32 time, f32 start, f32 change, f32 duration)
{
    time /= duration / 2.0f;
    if (time < 1)
    {
        return change / 2 * time * time * time + start;
    }
    else
    {
        time -= 2;
        return change / 2 * (time * time * time + 2) + start;
    }
}

#define ImplIsEven(type)                   \
    internal inline b32 mathIsEven(type n) \
    {                                      \
        return n % 2 == 0;                 \
    }

ImplIsEven(u8);
ImplIsEven(u16);
ImplIsEven(u32);
ImplIsEven(u64);
ImplIsEven(s8);
ImplIsEven(s16);
ImplIsEven(s32);
ImplIsEven(s64);

#define ImplIsOdd(type)                   \
    internal inline b32 mathIsOdd(type n) \
    {                                     \
        return n % 2 != 0;                \
    }

ImplIsOdd(u8);
ImplIsOdd(u16);
ImplIsOdd(u32);
ImplIsOdd(u64);
ImplIsOdd(s8);
ImplIsOdd(s16);
ImplIsOdd(s32);
ImplIsOdd(s64);

b32 mathIsPrime(u64 n);

internal inline u32 countDigits(u64 n)
{
    u32 result = 0;

    while (n)
    {
        n /= 10;
        ++result;
    }

    return result;
}

internal inline usize mathGetMaxIndex(u64 *values, usize count)
{
    usize result = 0;
    u64 max = 0;

    for (usize i = 0; i < count; ++i)
    {
        u64 temp = values[i];
        if (temp > max)
        {
            max = temp;
            result = i;
        }
    }

    return result;
}

#endif
