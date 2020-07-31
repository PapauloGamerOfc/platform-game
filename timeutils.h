#ifndef TIMEUTILS_H_INCLUDED
#define TIMEUTILS_H_INCLUDED
#define NANOS_PER_SECOND 1000000000

#include <time.h>

int getCurrentTime(struct timespec* time);

int addNanos(struct timespec *time, long long nanos);

int addSeconds(struct timespec *time, long double seconds);

long long getDelta(const struct timespec* start, const struct timespec* end);

#endif // TIMEUTILS_H_INCLUDED
