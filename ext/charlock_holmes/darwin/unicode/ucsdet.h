#ifndef __UCSDET_H
#define __UCSDET_H
#include "unicode/utypes.h"
#if !UCONFIG_NO_CONVERSION
#include "unicode/localpointer.h"
#include "unicode/uenum.h"
struct UCharsetDetector;
typedef struct UCharsetDetector UCharsetDetector;
struct UCharsetMatch;
typedef struct UCharsetMatch UCharsetMatch;
U_STABLE UCharsetDetector * U_EXPORT2
ucsdet_open(UErrorCode   *status);
U_STABLE void U_EXPORT2
ucsdet_close(UCharsetDetector *ucsd);
#if U_SHOW_CPLUSPLUS_API
U_NAMESPACE_BEGIN
U_DEFINE_LOCAL_OPEN_POINTER(LocalUCharsetDetectorPointer, UCharsetDetector, ucsdet_close);
U_NAMESPACE_END
#endif
U_STABLE void U_EXPORT2
ucsdet_setText(UCharsetDetector *ucsd, const char *textIn, int32_t len, UErrorCode *status);
U_STABLE void U_EXPORT2
ucsdet_setDeclaredEncoding(UCharsetDetector *ucsd, const char *encoding, int32_t length, UErrorCode *status);
U_STABLE const UCharsetMatch * U_EXPORT2
ucsdet_detect(UCharsetDetector *ucsd, UErrorCode *status);
U_STABLE const UCharsetMatch ** U_EXPORT2
ucsdet_detectAll(UCharsetDetector *ucsd, int32_t *matchesFound, UErrorCode *status);
U_STABLE const char * U_EXPORT2
ucsdet_getName(const UCharsetMatch *ucsm, UErrorCode *status);
U_STABLE int32_t U_EXPORT2
ucsdet_getConfidence(const UCharsetMatch *ucsm, UErrorCode *status);
U_STABLE const char * U_EXPORT2
ucsdet_getLanguage(const UCharsetMatch *ucsm, UErrorCode *status);
U_STABLE  int32_t U_EXPORT2
ucsdet_getUChars(const UCharsetMatch *ucsm,
                 UChar *buf, int32_t cap, UErrorCode *status);
U_STABLE  UEnumeration * U_EXPORT2
ucsdet_getAllDetectableCharsets(const UCharsetDetector *ucsd,  UErrorCode *status);
U_STABLE  UBool U_EXPORT2
ucsdet_isInputFilterEnabled(const UCharsetDetector *ucsd);
U_STABLE  UBool U_EXPORT2
ucsdet_enableInputFilter(UCharsetDetector *ucsd, UBool filter);
#endif
#endif
