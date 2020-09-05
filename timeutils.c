#include "timeutils.h"

#include <time.h>

int getCurrentTime(struct timespec* time)
{
    clock_gettime(CLOCK_MONOTONIC, time);
    return 0;
}

int addNanos(struct timespec *time, long long nanos)
{
    time->tv_sec += (nanos / NANOS_PER_SECOND);
    nanos %= NANOS_PER_SECOND;
    time->tv_nsec += nanos;
    time->tv_sec += (time->tv_nsec / NANOS_PER_SECOND);
    time->tv_nsec %= NANOS_PER_SECOND;
    return 0;
}

int addSeconds(struct timespec *time, float seconds)
{
    int intSeconds = (int) seconds;
    time->tv_sec += intSeconds;
    seconds -= intSeconds;
    if(seconds != 0.0)
    {
        time->tv_nsec += (seconds * NANOS_PER_SECOND);
        time->tv_sec += (time->tv_nsec / NANOS_PER_SECOND);
        time->tv_nsec %= NANOS_PER_SECOND;
    }
    return 0;
}

long long getDelta(const struct timespec* start, const struct timespec* end)
{
    if(start == NULL || end == NULL) return 0;
    return ((long long) end->tv_sec - start->tv_sec) * NANOS_PER_SECOND + ((long long) end->tv_nsec - start->tv_nsec);
}
