#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

#define LOGINFO(fmt, ...) printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define LOGERROR(fmt, ...) printf("[ERROR] " fmt "\n", ##__VA_ARGS__)

#define true 1
#define false 0

typedef uint8_t u8;   // 0 - 255
typedef uint16_t u16; // 0 - 65,535
typedef uint32_t u32; // 0 - 4,294,967,295
typedef uint64_t u64; // 0 - 18,446,744,073,709,551,615
typedef double f64;

#endif // _UTIL_H_