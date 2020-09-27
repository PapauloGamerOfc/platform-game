#ifndef TIMEUTILS_H_INCLUDED
#define TIMEUTILS_H_INCLUDED
#define NANOS_PER_SECOND 1000000000

#include <time.h>
#include <stdint.h>

void getCurrentTime(struct timespec* time);

void addNanos(struct timespec *time, int64_t nanos);

void addSeconds(struct timespec *time, float seconds);

int64_t getDelta(const struct timespec* start, const struct timespec* end);

#endif // TIMEUTILS_H_INCLUDED