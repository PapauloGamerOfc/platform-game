#include "mathutils.h"

long double dabsd(long double val)
{
    return val >= 0.0 ? val : -val;
}

int iabsi(int val)
{
    return val >= 0 ? val : -val;
}

long long lminl(long long a, long long b)
{
    return (a < b) ? a : b;
}

long long lmaxl(long long a, long long b)
{
    return (a > b) ? a : b;
}

int imini(int a, int b)
{
    return (a < b) ? a : b;
}

int imaxi(int a, int b)
{
    return (a > b) ? a : b;
}

void clamp(long double* val, long double min, long double max)
{
   if(*val < min)
        *val = min;
    if(*val > max)
        *val = max;
}
