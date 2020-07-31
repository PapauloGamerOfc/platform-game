#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

long double dabsd(long double val);

int iabsi(int val);

long long lminl(long long a, long long b);

long long lmaxl(long long a, long long b);

int imini(int a, int b);

int imaxi(int a, int b);

void clamp(long double* val, long double min, long double max);

#endif // MATHUTILS_H_INCLUDED
