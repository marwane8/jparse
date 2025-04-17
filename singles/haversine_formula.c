/* ========================================================================

   (C) Copyright 2023 by Molly Rocket, Inc., All Rights Reserved.

/* ======================================================================== */

#include <stdint.h>
#include <math.h>

typedef uint8_t u8;   // 0 - 255
typedef uint16_t u16; // 0 - 65,535
typedef uint32_t u32; // 0 - 4,294,967,295
typedef uint64_t u64; // 0 - 18,446,744,073,709,551,615
typedef double f64;

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
