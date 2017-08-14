#ifndef __UENUM_H
#define __UENUM_H
#include "unicode/utypes.h"
#include "unicode/localpointer.h"
#if U_SHOW_CPLUSPLUS_API
#include "unicode/strenum.h"
#endif
struct UEnumeration;
typedef struct UEnumeration UEnumeration;
U_STABLE void U_EXPORT2
uenum_close(UEnumeration* en);
#if U_SHOW_CPLUSPLUS_API
U_NAMESPACE_BEGIN
U_DEFINE_LOCAL_OPEN_POINTER(LocalUEnumerationPointer, UEnumeration, uenum_close);
U_NAMESPACE_END
#endif
U_STABLE int32_t U_EXPORT2
uenum_count(UEnumeration* en, UErrorCode* status);
U_STABLE const UChar* U_EXPORT2
uenum_unext(UEnumeration* en,
            int32_t* resultLength,
            UErrorCode* status);
U_STABLE const char* U_EXPORT2
uenum_next(UEnumeration* en,
           int32_t* resultLength,
           UErrorCode* status);
U_STABLE void U_EXPORT2
uenum_reset(UEnumeration* en, UErrorCode* status);
#if U_SHOW_CPLUSPLUS_API
U_CAPI UEnumeration* U_EXPORT2
uenum_openFromStringEnumeration(U_NAMESPACE_QUALIFIER StringEnumeration* adopted, UErrorCode* ec);
#endif
#endif
