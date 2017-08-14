#ifndef _PLATFORM_H
#define _PLATFORM_H
#if defined(UVERNUM_H)
# error Do not include unicode/uvernum.h before #including unicode/platform.h.  Instead of unicode/uvernum.h, #include unicode/uversion.h
#endif
#ifndef UCLN_NO_AUTO_CLEANUP
#define UCLN_NO_AUTO_CLEANUP 1
#endif
#ifndef CYGWINMSVC
#ifndef U_DARWIN
#define U_DARWIN
#endif
#ifndef U_HAVE_DIRENT_H
#define U_HAVE_DIRENT_H 1
#endif
#ifndef U_HAVE_INTTYPES_H
#define U_HAVE_INTTYPES_H 1
#endif
#ifndef U_IOSTREAM_SOURCE
#define U_IOSTREAM_SOURCE 199711
#endif
#ifndef U_HAVE_STD_STRING
#define U_HAVE_STD_STRING 1
#endif
#ifndef U_HAVE_INT8_T
#define U_HAVE_INT8_T 1
#endif
#ifndef U_HAVE_UINT8_T
#define U_HAVE_UINT8_T 1
#endif
#ifndef U_HAVE_INT16_T
#define U_HAVE_INT16_T 1
#endif
#ifndef U_HAVE_UINT16_T
#define U_HAVE_UINT16_T 1
#endif
#ifndef U_HAVE_INT32_T
#define U_HAVE_INT32_T 1
#endif
#ifndef U_HAVE_UINT32_T
#define U_HAVE_UINT32_T 1
#endif
#ifndef U_HAVE_INT64_T
#define U_HAVE_INT64_T 1
#endif
#ifndef U_HAVE_UINT64_T
#define U_HAVE_UINT64_T 1
#endif
#ifndef U_HAVE_NAMESPACE
#define U_HAVE_NAMESPACE 1
#endif
#if defined(BYTE_ORDER) && defined(BIG_ENDIAN)
#define U_IS_BIG_ENDIAN (BYTE_ORDER == BIG_ENDIAN)
#else
#define U_IS_BIG_ENDIAN 0
#endif
#ifndef ICU_USE_THREADS
#define ICU_USE_THREADS 1
#endif
#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#define UMTX_STRONG_MEMORY_MODEL 1
#endif
#ifndef U_DEBUG
#define U_DEBUG 0
#endif
#ifndef U_RELEASE
#define U_RELEASE 1
#endif
#ifndef U_DISABLE_RENAMING
#define U_DISABLE_RENAMING 1
#endif
#ifndef U_OVERRIDE_CXX_ALLOCATION
#define U_OVERRIDE_CXX_ALLOCATION 1
#endif
#ifndef U_HAVE_PLACEMENT_NEW
#define U_HAVE_PLACEMENT_NEW 1
#endif
#ifndef U_ENABLE_TRACING
#define U_ENABLE_TRACING 0
#endif
#ifndef U_ENABLE_DYLOAD
#define U_ENABLE_DYLOAD 1
#endif
#ifndef U_CHECK_DYLOAD
#define U_CHECK_DYLOAD 1
#endif
#ifndef U_DEFAULT_SHOW_DRAFT
#define U_DEFAULT_SHOW_DRAFT 1
#endif
#if ((defined(OS390) && (!defined(__CHARSET_LIB) || !__CHARSET_LIB))) || defined(OS400)
#   define U_CHARSET_FAMILY 1
#endif
#ifndef U_HAVE_WCHAR_H
#define U_HAVE_WCHAR_H      1
#endif
#ifndef U_SIZEOF_WCHAR_T
#define U_SIZEOF_WCHAR_T    4
#endif
#ifndef U_HAVE_WCSCPY
#define U_HAVE_WCSCPY       1
#endif
#ifndef U_GNUC_UTF16_STRING
#define U_GNUC_UTF16_STRING 0
#endif
#if 1 || defined(U_CHECK_UTF16_STRING)
#if (defined(__xlC__) && defined(__IBM_UTF_LITERAL) && U_SIZEOF_WCHAR_T != 2) \
    || (defined(__HP_aCC) && __HP_aCC >= 035000) \
    || (defined(__HP_cc) && __HP_cc >= 111106) \
    || U_GNUC_UTF16_STRING
#define U_DECLARE_UTF16(string) u ## string
#elif (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x550)
#define U_DECLARE_UTF16(string) U ## string
#elif U_SIZEOF_WCHAR_T == 2 \
    && (U_CHARSET_FAMILY == 0 || ((defined(OS390) || defined(OS400)) && defined(__UCS2__)))
#define U_DECLARE_UTF16(string) L ## string
#endif
#endif
#ifndef U_HAVE_NL_LANGINFO_CODESET
#define U_HAVE_NL_LANGINFO_CODESET  1
#endif
#ifndef U_NL_LANGINFO_CODESET
#define U_NL_LANGINFO_CODESET       CODESET
#endif
#if 1
#define U_TZSET         tzset
#endif
#if 1
#define U_TIMEZONE      timezone
#endif
#if 1
#define U_TZNAME        tzname
#endif
#define U_HAVE_MMAP     1
#define U_HAVE_POPEN    1
#if 1
#define U_EXPORT __attribute__((visibility("default")))
#elif (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x550) \
   || (defined(__SUNPRO_C) && __SUNPRO_C >= 0x550)
#define U_EXPORT __global
#else
#define U_EXPORT
#endif
#define U_EXPORT2
#if defined(U_CYGWIN) && !defined(__GNUC__)
#define U_IMPORT __declspec(dllimport)
#else
#define U_IMPORT
#endif
#ifndef U_INLINE
#   ifdef __cplusplus
#       define U_INLINE inline
#   else
#       define U_INLINE __inline__
#   endif
#endif
#ifndef U_ALIGN_CODE
#define U_ALIGN_CODE(n)
#endif
#ifndef U_HAVE_GCC_ATOMICS
#define U_HAVE_GCC_ATOMICS 1
#endif
#ifndef U_MAKE
#define U_MAKE  "/usr/bin/gnumake"
#endif
#endif
# define U_LIB_SUFFIX_C_NAME
# define U_LIB_SUFFIX_C_NAME_STRING ""
# define U_HAVE_LIB_SUFFIX 0
#if U_HAVE_LIB_SUFFIX
# ifndef U_ICU_ENTRY_POINT_RENAME
#  define U_ICU_ENTRY_POINT_RENAME(x)    x ## _ ## 46 ##
#  define U_DEF_ICUDATA_ENTRY_POINT(major, minor) icudt####major##minor##_dat
# endif
#endif
#endif
