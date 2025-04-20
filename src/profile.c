
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include "profile.h"
#include "assert.h"

void init_profile()
{
    PROFILE_COUNT = 0;
    strncpy(COUNTER_ARRAY[0].label, "entry", COUNTER_NAME_MAX);
    COUNTER_ARRAY[0].time = 0;
    clock_gettime(CLOCK_MONOTONIC, &COUNTER_ARRAY[0].last_ref);
    PROFILE_COUNT++;
}

u16 start_count(char *name)
{
    strncpy(COUNTER_ARRAY[PROFILE_COUNT].label, name, COUNTER_NAME_MAX);
    clock_gettime(CLOCK_MONOTONIC, &COUNTER_ARRAY[PROFILE_COUNT].last_ref);
    return PROFILE_COUNT++;
}

u64 time_diff(struct timespec t1, struct timespec t2)
{
    return (t2.tv_sec - t1.tv_sec) * NANO + (t2.tv_nsec - t1.tv_nsec);
};

void print_counter()
{

    f64 elapsed = COUNTER_ARRAY[0].time;
    u64 accumilator = 0;
    printf("total time:     %.0f (%.3f sec)  \n\n", elapsed, (double)elapsed / NANO);
    for (int i = 1; i < PROFILE_COUNT; i++)
    {
        f64 percent = ((double)COUNTER_ARRAY[i].time / COUNTER_ARRAY[0].time) * 100;
        printf("%s time:    %llu (%.5f %%) \n", COUNTER_ARRAY[i].label, COUNTER_ARRAY[i].time, percent);
        accumilator = accumilator + COUNTER_ARRAY[i].time;
    }

    f64 percent = ((double)accumilator / COUNTER_ARRAY[0].time) * 100;
    printf("\n\nfunction percent: (%.5f %%) \n", percent);
}

void end_count(u16 count_id)
{
    assert(count_id < COUNTER_BUFFER_MAX || COUNTER_ARRAY[count_id].time == 0);
    ns_time end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    COUNTER_ARRAY[count_id].time = time_diff(COUNTER_ARRAY[count_id].last_ref, end);
}

void end_profile()
{
    ns_time end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    COUNTER_ARRAY[0].time = time_diff(COUNTER_ARRAY[0].last_ref, end);
    print_counter();
}
