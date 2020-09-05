#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

float fabsf(float val);

int iabsi(int val);

long long lminl(long long a, long long b);

long long lmaxl(long long a, long long b);

int imini(int a, int b);

int imaxi(int a, int b);

void clamp(float *val, float min, float max);

#endif // MATHUTILS_H_INCLUDED
