#ifndef __UMACHINE_H__
#define __UMACHINE_H__
#if defined(U_PALMOS)
#   include "unicode/ppalmos.h"
#elif !defined(__MINGW32__) && (defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64))
#ifdef CYGWINMSVC
#   include "unicode/platform.h"
#endif
#   include "unicode/pwin32.h"
#else
#   include "unicode/ptypes.h"
#endif
#include <stddef.h>
#ifdef __cplusplus
#   ifndef XP_CPLUSPLUS
#       define XP_CPLUSPLUS
#   endif
#else
#   undef XP_CPLUSPLUS
#endif
#ifdef XP_CPLUSPLUS
#   define U_CFUNC extern "C"
#   define U_CDECL_BEGIN extern "C" {
#   define U_CDECL_END   }
#else
#   define U_CFUNC extern
#   define U_CDECL_BEGIN
#   define U_CDECL_END
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 2))
#    define U_ATTRIBUTE_DEPRECATED __attribute__ ((deprecated))
#elif defined(U_WINDOWS) && defined(_MSC_VER) && (_MSC_VER >= 1400)
#    define U_ATTRIBUTE_DEPRECATED __declspec(deprecated)
#else
#    define U_ATTRIBUTE_DEPRECATED
#endif
#define U_CAPI U_CFUNC U_EXPORT
#define U_STABLE U_CAPI
#define U_DRAFT  U_CAPI
#define U_DEPRECATED U_CAPI U_ATTRIBUTE_DEPRECATED
#define U_OBSOLETE U_CAPI
#define U_INTERNAL U_CAPI
#ifndef INT8_MIN
#   define INT8_MIN        ((int8_t)(-128))
#endif
#ifndef INT16_MIN
#   define INT16_MIN       ((int16_t)(-32767-1))
#endif
#ifndef INT32_MIN
#   define INT32_MIN       ((int32_t)(-2147483647-1))
#endif
#ifndef INT8_MAX
#   define INT8_MAX        ((int8_t)(127))
#endif
#ifndef INT16_MAX
#   define INT16_MAX       ((int16_t)(32767))
#endif
#ifndef INT32_MAX
#   define INT32_MAX       ((int32_t)(2147483647))
#endif
#ifndef UINT8_MAX
#   define UINT8_MAX       ((uint8_t)(255U))
#endif
#ifndef UINT16_MAX
#   define UINT16_MAX      ((uint16_t)(65535U))
#endif
#ifndef UINT32_MAX
#   define UINT32_MAX      ((uint32_t)(4294967295U))
#endif
#if defined(U_INT64_T_UNAVAILABLE)
# error int64_t is required for decimal format and rule-based number format.
#else
# ifndef INT64_C
#   define INT64_C(c) c ## LL
# endif
# ifndef UINT64_C
#   define UINT64_C(c) c ## ULL
# endif
# ifndef U_INT64_MIN
#     define U_INT64_MIN       ((int64_t)(INT64_C(-9223372036854775807)-1))
# endif
# ifndef U_INT64_MAX
#     define U_INT64_MAX       ((int64_t)(INT64_C(9223372036854775807)))
# endif
# ifndef U_UINT64_MAX
#     define U_UINT64_MAX      ((uint64_t)(UINT64_C(18446744073709551615)))
# endif
#endif
typedef int8_t UBool;
#ifndef TRUE
#   define TRUE  1
#endif
#ifndef FALSE
#   define FALSE 0
#endif
#ifndef U_HAVE_WCHAR_H
#   define U_HAVE_WCHAR_H 1
#endif
#if U_SIZEOF_WCHAR_T==0
#   undef U_SIZEOF_WCHAR_T
#   define U_SIZEOF_WCHAR_T 4
#endif
#if !defined(U_WCHAR_IS_UTF16) && !defined(U_WCHAR_IS_UTF32)
#   ifdef __STDC_ISO_10646__
#       if (U_SIZEOF_WCHAR_T==2)
#           define U_WCHAR_IS_UTF16
#       elif (U_SIZEOF_WCHAR_T==4)
#           define  U_WCHAR_IS_UTF32
#       endif
#   elif defined __UCS2__
#       if (__OS390__ || __OS400__) && (U_SIZEOF_WCHAR_T==2)
#           define U_WCHAR_IS_UTF16
#       endif
#   elif defined __UCS4__
#       if (U_SIZEOF_WCHAR_T==4)
#           define U_WCHAR_IS_UTF32
#       endif
#   elif defined(U_WINDOWS)
#       define U_WCHAR_IS_UTF16
#   endif
#endif
#define U_SIZEOF_UCHAR 2
#if U_SIZEOF_WCHAR_T==2
    typedef wchar_t UChar;
#elif U_GNUC_UTF16_STRING
#if defined _GCC_
    typedef __CHAR16_TYPE__ char16_t;
#endif
    typedef char16_t UChar;
#else
    typedef uint16_t UChar;
#endif
typedef int32_t UChar32;
#ifndef U_HIDE_INTERNAL_API
#ifndef U_ALIGN_CODE
#   define U_ALIGN_CODE(n)
#endif
#endif
#ifndef U_INLINE
#   ifdef XP_CPLUSPLUS
#       define U_INLINE inline
#   else
#       define U_INLINE
#   endif
#endif
#include "unicode/urename.h"
#endif
