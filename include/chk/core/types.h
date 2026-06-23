#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef void* Ptr;
typedef void* Handle;

typedef bool B8;
typedef char C8;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t  S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef float  F32;
typedef double F64;

typedef size_t    Size;
typedef size_t    Index;
typedef ptrdiff_t Offset;

typedef char*       Str;
typedef const char* CStr;

typedef va_list Args;
#define Args_Init(args, fmt) va_start(args, fmt)
#define Args_Destroy(args)   va_end(args)
#define Args_Copy(dst, src)  va_copy(dst, src)
#define Args_Get(args, Type) va_arg(args, Type)

#define SizeOf(val)            (sizeof(val))
#define CountOf(arr)           (sizeof(arr) / sizeof((arr)[0]))
#define AlignOf(Type)          _Alignof(Type)
#define OffsetOf(Type, member) offsetof(Type, member)

#define Kilobytes(val) (1024ULL * (val))
#define Megabytes(val) (1024ULL * Kilobytes(val))
#define Gigabytes(val) (1024ULL * Megabytes(val))
#define Terabytes(val) (1024ULL * Gigabytes(val))
