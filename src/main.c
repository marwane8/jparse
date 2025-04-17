#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "str_vector.h"
#include "json_parse.h"
#include "haversine.c"

int read_to_buffer(FILE *fp, str_vec *buffer)
{
    char c;
    while ((c = getc(fp)) != EOF)
    {
        strv_addc(buffer, c);
    }
    return 0;
}

int main(int argc, char *argv[])
{

    ntime start, t1, t2, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    FILE *file;
    str_vec buffer;
    strv_init(&buffer);

    if (argc <= 1)
    {
        printf("\tUsage: jparse <file.json>\n");
        return 0;
    }

    char *filename = argv[1];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        LOGERROR("file not found: %s", filename);
        exit(EXIT_FAILURE);
        return 1;
    }

    read_to_buffer(file, &buffer);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    json_node *JSON = parse_json(buffer);
    clock_gettime(CLOCK_MONOTONIC, &t2);

    int total = 100;
    f64 EARTH_R = 6372.8;

    haversine_pair *pairs = parse_haversine(JSON, total);
    f64 answer[total], sum;
    for (u32 i = 0; i < total; i++)
    {
        haversine_pair p = pairs[i];
        answer[i] = calc_haversine(p.x0, p.y0, p.x1, p.y1, EARTH_R);
        sum = sum + answer[i];
    };

    f64 average = sum / total;
    clock_gettime(CLOCK_MONOTONIC, &end);

    f64 elapsed = time_diff(start, end);
    u64 file_read_time = time_diff(start, t1);
    u64 json_parse_time = time_diff(t1, t2);
    u64 calc_haversine_time = time_diff(t2, end);

    printf("Average: %.16f\n\n", average);

    printf("total time:     %0.2f | %0.3f sec \n", elapsed, (elapsed / 1000000000LL));
    printf("file read time: %llu  (%0.2f %%)\n", file_read_time, (file_read_time / elapsed) * 100);
    printf("json parse time:%llu  (%0.2f %%)\n", json_parse_time, (json_parse_time / elapsed) * 100);
    printf("json calc time: %llu  (%0.2f %%)\n", calc_haversine_time, (calc_haversine_time / elapsed) * 100);
}
