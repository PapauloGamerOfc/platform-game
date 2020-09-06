#ifndef MATHUTILS_H_INCLUDED
#define MATHUTILS_H_INCLUDED

#include <stdint.h>

float fabsf(float val);

int32_t iabsi(int32_t val);

int64_t lminl(int64_t a, int64_t b);

int64_t lmaxl(int64_t a, int64_t b);

int32_t imini(int32_t a, int32_t b);

int32_t imaxi(int32_t a, int32_t b);

void clamp(float *val, float min, float max);

#endif // MATHUTILS_H_INCLUDED
