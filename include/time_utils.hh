#pragma once

#include <time.h>

#define MAX(a, b)           \
({                          \
    typeof(a) _a = (a);     \
    typeof(b) _b = (b);     \
    _a >= _b ? _a : _b;     \
})

#define MIN(a, b)           \
({                          \
    typeof(a) _a = (a);     \
    typeof(b) _b = (b);     \
    _a <= _b ? _a : _b;     \
})

#define GETTIME(t) (clock_gettime(CLOCK_MONOTONIC, &(t)))
#define DIFF(t1, t2) (timespec_diff(t1, t2))

typedef struct timespec timespec;

inline float timespec_diff(timespec t1, timespec t2)
{
    timespec result;
    if ((t2.tv_nsec - t1.tv_nsec) < 0) {
        result.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        result.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        result.tv_sec = t2.tv_sec - t1.tv_sec;
        result.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return result.tv_sec * 1e9 + result.tv_nsec;
}
