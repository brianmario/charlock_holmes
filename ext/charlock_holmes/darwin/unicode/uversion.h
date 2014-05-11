#ifndef UVERSION_H
#define UVERSION_H
#include "unicode/umachine.h"
#include "unicode/uvernum.h"
#define U_COPYRIGHT_STRING_LENGTH  128
#define U_MAX_VERSION_LENGTH 4
#define U_VERSION_DELIMITER '.'
#define U_MAX_VERSION_STRING_LENGTH 20
typedef uint8_t UVersionInfo[U_MAX_VERSION_LENGTH];
#ifdef XP_CPLUSPLUS
#if U_HAVE_NAMESPACE
#   if U_DISABLE_RENAMING
#       define U_ICU_NAMESPACE icu
        namespace U_ICU_NAMESPACE { }
#   else
#       define U_ICU_NAMESPACE U_ICU_ENTRY_POINT_RENAME(icu)
        namespace U_ICU_NAMESPACE { }
        namespace icu = U_ICU_NAMESPACE;
#   endif
#   define U_NAMESPACE_BEGIN extern "C++" { namespace U_ICU_NAMESPACE {
#   define U_NAMESPACE_END } }
#   define U_NAMESPACE_USE using namespace U_ICU_NAMESPACE;
#   define U_NAMESPACE_QUALIFIER U_ICU_NAMESPACE::
#   ifndef U_USING_ICU_NAMESPACE
#       define U_USING_ICU_NAMESPACE 1
#   endif
#   if U_USING_ICU_NAMESPACE
        U_NAMESPACE_USE
#   endif
#else
#   define U_NAMESPACE_BEGIN extern "C++" {
#   define U_NAMESPACE_END }
#   define U_NAMESPACE_USE
#   define U_NAMESPACE_QUALIFIER
#endif
#else
#   define U_NAMESPACE_BEGIN
#   define U_NAMESPACE_END
#   define U_NAMESPACE_USE
#   define U_NAMESPACE_QUALIFIER
#endif
U_STABLE void U_EXPORT2
u_versionFromString(UVersionInfo versionArray, const char *versionString);
U_STABLE void U_EXPORT2
u_versionFromUString(UVersionInfo versionArray, const UChar *versionString);
U_STABLE void U_EXPORT2
u_versionToString(UVersionInfo versionArray, char *versionString);
U_STABLE void U_EXPORT2
u_getVersion(UVersionInfo versionArray);
#endif
