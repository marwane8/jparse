
#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "util.h"

typedef struct timespec ns_time;
#define COUNTER_NAME_MAX 128
#define COUNTER_BUFFER_MAX 1024
#define NANO 1000000000LL 

typedef struct _counter
{
    char label[COUNTER_NAME_MAX];
    ns_time last_ref;
    u64 time;
} counter;

static counter COUNTER_ARRAY[COUNTER_BUFFER_MAX] = {};
static u16 PROFILE_COUNT;

void init_profile();
void end_profile();
u16 start_count(char *name);
void end_count(u16 count_id);

#endif // _PROFILE_H_
