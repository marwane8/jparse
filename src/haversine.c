#include <stdlib.h>
#include <math.h>

#include "util.h"
#include "json_parse.h"

typedef struct _haversine_pair
{
    f64 x0;
    f64 y0;
    f64 x1;
    f64 y1;
} haversine_pair;

haversine_pair *parse_haversine(json_node *JSON, u32 count)
{
    json_node *node_pairs = lookup_node(JSON, "pairs");
    json_node *curr_pair = node_pairs->json_child;

    haversine_pair *pairs = malloc(sizeof(haversine_pair) * count);
    u32 idx = 0;

    while (curr_pair && idx < count)
    {
        json_node *curr = lookup_node(curr_pair, "x0");

        pairs[idx].x0 = atof(strv_get(curr->value));
        curr = curr->json_next;

        pairs[idx].y0 = atof(strv_get(curr->value));
        curr = curr->json_next;

        pairs[idx].x1 = atof(strv_get(curr->value));
        curr = curr->json_next;

        pairs[idx].y1 = atof(strv_get(curr->value));
        curr = curr->json_next;

        idx++;
        curr_pair = curr_pair->json_next;
    }

    return pairs;
}

void print_hv(haversine_pair p)
{
    printf("x0: %.16f, y0: %.16f - x1:%.16f, y1:%.16f\n", p.x0, p.y0, p.x1, p.y1);
}


/* ======================================
HAVERSINE FORMULA IMPLEMENTATION
   ======================================*/

static f64 square(f64 A)
{
    f64 res = (A * A);
    return res;
}

static f64 degree2radian(f64 degrees)
{
    f64 res = 0.01745329251994329577 * degrees;
    return res;
}

// NOTE(casey): earth_radius is generally expected to be 6372.8
static f64 calc_haversine(f64 X0, f64 Y0, f64 X1, f64 Y1, f64 earth_radius)
{
    f64 lat1 = Y0;
    f64 lat2 = Y1;
    f64 lon1 = X0;
    f64 lon2 = X1;

    f64 dLat = degree2radian(lat2 - lat1);
    f64 dLon = degree2radian(lon2 - lon1);
    
    lat1 = degree2radian(lat1);
    lat2 = degree2radian(lat2);

    f64 a = square(sin(dLat / 2.0)) + cos(lat1) * cos(lat2) * square(sin(dLon / 2));
    f64 c = 2.0 * asin(sqrt(a));

    f64 res = earth_radius * c;
    return res;
}
