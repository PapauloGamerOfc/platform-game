#include "timeutils.h"

#include <time.h>
#include <stdint.h>

void getCurrentTime(struct timespec* time)
{
    clock_gettime(CLOCK_MONOTONIC, time);
}

void addNanos(struct timespec *time, int64_t nanos)
{
    time->tv_sec += (nanos / NANOS_PER_SECOND);
    nanos %= NANOS_PER_SECOND;
    time->tv_nsec += nanos;
    time->tv_sec += (time->tv_nsec / NANOS_PER_SECOND);
    time->tv_nsec %= NANOS_PER_SECOND;
}

void addSeconds(struct timespec *time, float seconds)
{
    int32_t intSeconds = (int32_t) seconds;
    time->tv_sec += intSeconds;
    seconds -= intSeconds;
    if(seconds != 0.0)
    {
        time->tv_nsec += (seconds * NANOS_PER_SECOND);
        time->tv_sec += (time->tv_nsec / NANOS_PER_SECOND);
        time->tv_nsec %= NANOS_PER_SECOND;
    }
}

int64_t getDelta(const struct timespec* start, const struct timespec* end)
{
    if(start == NULL || end == NULL) return 0;
    return ((int64_t) end->tv_sec - start->tv_sec) * NANOS_PER_SECOND + ((int64_t) end->tv_nsec - start->tv_nsec);
}
