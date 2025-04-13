#ifndef _MACROS_H_
#define _MACROS_H_

#include <stdint.h>

#define LOGINFO(msg) printf("[INFO] %s\n", msg)
#define LOGERROR(msg) printf("[ERROR] %s\n", msg)

typedef uint8_t u8;     // 0 - 255
typedef uint16_t u16;   // 0 - 65,535
typedef uint32_t u32;   // 0 - 4,294,967,295
typedef uint64_t u64;   // 0 - 18,446,744,073,709,551,615

#endif