#ifndef ISA_DEFINES_H

#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#if !defined(_cplusplus)
#define bool uint64_t
#define true  (1)
#define false (0)
#endif

#define ISA_DEFINES_H
#endif