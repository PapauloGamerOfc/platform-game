#include "mathutils.h"
#include <stdint.h>

float fabsf(float val)
{
    return val >= 0.0 ? val : -val;
}

int32_t iabsi(int32_t val)
{
    return val >= 0 ? val : -val;
}

int64_t lminl(int64_t a, int64_t b)
{
    return (a < b) ? a : b;
}

int64_t lmaxl(int64_t a, int64_t b)
{
    return (a > b) ? a : b;
}

int32_t imini(int32_t a, int32_t b)
{
    return (a < b) ? a : b;
}

int32_t imaxi(int32_t a, int32_t b)
{
    return (a > b) ? a : b;
}

void clamp(float *val, float min, float max)
{
   if(*val < min)
        *val = min;
    if(*val > max)
        *val = max;
}
