#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "str_vector.h"
#include "json_parse.h"
#include "haversine.c"
#include "profile.h"

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

    init_profile();

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
    int read_id = start_count("read file");
    read_to_buffer(file, &buffer);
    end_count(read_id);

    json_node *JSON = parse_json(buffer);

    int total = 100;
    f64 EARTH_R = 6372.8;

    int parse_id = start_count("parse");
    haversine_pair *pairs = parse_haversine(JSON, total);
    end_count(parse_id);

    int calc = start_count("calculate");
    f64 answer[total], sum;
    for (u32 i = 0; i < total; i++)
    {
        haversine_pair p = pairs[i];
        answer[i] = calc_haversine(p.x0, p.y0, p.x1, p.y1, EARTH_R);
        sum = sum + answer[i];
    };
    end_count(calc);

    end_profile();
}
