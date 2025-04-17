#include "util.h"

u64 time_diff(struct timespec t1, struct timespec t2)
{
    return (t2.tv_sec - t1.tv_sec) * 1000000000LL + (t2.tv_nsec - t1.tv_nsec);
}