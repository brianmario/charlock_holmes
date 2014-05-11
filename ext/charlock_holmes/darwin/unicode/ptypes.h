#ifndef _PTYPES_H
#define _PTYPES_H
#include <sys/types.h>
#include "unicode/platform.h"
#if U_HAVE_INTTYPES_H
#ifdef OS390
#include <features.h>
#if ! U_HAVE_INT8_T
typedef signed char int8_t;
#endif
#if !defined(__uint8_t)
#define __uint8_t 1
typedef unsigned char uint8_t;
#endif
#endif
#include <inttypes.h>
#else
#if ! U_HAVE_INT8_T
typedef signed char int8_t;
#endif
#if ! U_HAVE_UINT8_T
typedef unsigned char uint8_t;
#endif
#if ! U_HAVE_INT16_T
typedef signed short int16_t;
#endif
#if ! U_HAVE_UINT16_T
typedef unsigned short uint16_t;
#endif
#if ! U_HAVE_INT32_T
typedef signed int int32_t;
#endif
#if ! U_HAVE_UINT32_T
typedef unsigned int uint32_t;
#endif
#if ! U_HAVE_INT64_T
    typedef signed long long int64_t;
#endif
#if ! U_HAVE_UINT64_T
    typedef unsigned long long uint64_t;
#endif
#endif
#endif
