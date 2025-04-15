#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "util.h"

u64 time_diff(struct timespec t1, struct timespec t2)
{

    return (t2.tv_sec - t1.tv_sec) * 1000000000LL + (t2.tv_nsec - t1.tv_nsec);
}

int main()
{
    clock_t rstart, rend;
    struct timespec tstart, tend;
    rstart = clock();
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    tend = tstart;

    while ((clock() - rstart) < CLOCKS_PER_SEC)
        ;
    sleep(1);
    rend = clock();
    clock_gettime(CLOCK_MONOTONIC, &tend);
    LOGINFO("timepsec time:  %llu", time_diff(tstart, tend));
    LOGINFO("clock time:     %lu", (rend - rstart));
}