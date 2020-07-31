#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <time.h>

int getCurrentTime(struct timespec* time);

long long getDelta(struct timespec* start, struct timespec* end);

#endif // TIME_H_INCLUDED
