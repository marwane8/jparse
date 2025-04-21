#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long long time_diff(struct timespec t1, struct timespec t2)
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
    printf("timepsec time:  %llu\n", time_diff(tstart, tend));
    printf("clock time:     %lu\n", (rend - rstart));
}