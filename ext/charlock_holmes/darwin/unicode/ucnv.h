#ifndef UCNV_H
#define UCNV_H
#include "unicode/ucnv_err.h"
#include "unicode/uenum.h"
#include "unicode/localpointer.h"
#ifndef __USET_H__
struct USet;
typedef struct USet USet;
#endif
#if !UCONFIG_NO_CONVERSION
U_CDECL_BEGIN
#define UCNV_MAX_CONVERTER_NAME_LENGTH 60
#define UCNV_MAX_FULL_FILE_NAME_LENGTH (600+UCNV_MAX_CONVERTER_NAME_LENGTH)
#define  UCNV_SI 0x0F
#define  UCNV_SO 0x0E
typedef enum {
    UCNV_UNSUPPORTED_CONVERTER = -1,
    UCNV_SBCS = 0,
    UCNV_DBCS = 1,
    UCNV_MBCS = 2,
    UCNV_LATIN_1 = 3,
    UCNV_UTF8 = 4,
    UCNV_UTF16_BigEndian = 5,
    UCNV_UTF16_LittleEndian = 6,
    UCNV_UTF32_BigEndian = 7,
    UCNV_UTF32_LittleEndian = 8,
    UCNV_EBCDIC_STATEFUL = 9,
    UCNV_ISO_2022 = 10,
    UCNV_LMBCS_1 = 11,
    UCNV_LMBCS_2,
    UCNV_LMBCS_3,
    UCNV_LMBCS_4,
    UCNV_LMBCS_5,
    UCNV_LMBCS_6,
    UCNV_LMBCS_8,
    UCNV_LMBCS_11,
    UCNV_LMBCS_16,
    UCNV_LMBCS_17,
    UCNV_LMBCS_18,
    UCNV_LMBCS_19,
    UCNV_LMBCS_LAST = UCNV_LMBCS_19,
    UCNV_HZ,
    UCNV_SCSU,
    UCNV_ISCII,
    UCNV_US_ASCII,
    UCNV_UTF7,
    UCNV_BOCU1,
    UCNV_UTF16,
    UCNV_UTF32,
    UCNV_CESU8,
    UCNV_IMAP_MAILBOX,
    UCNV_NUMBER_OF_SUPPORTED_CONVERTER_TYPES
} UConverterType;
typedef enum {
    UCNV_UNKNOWN = -1,
    UCNV_IBM = 0
} UConverterPlatform;
typedef void (U_EXPORT2 *UConverterToUCallback) (
                  const void* context,
                  UConverterToUnicodeArgs *args,
                  const char *codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode *pErrorCode);
typedef void (U_EXPORT2 *UConverterFromUCallback) (
                    const void* context,
                    UConverterFromUnicodeArgs *args,
                    const UChar* codeUnits,
                    int32_t length,
                    UChar32 codePoint,
                    UConverterCallbackReason reason,
                    UErrorCode *pErrorCode);
U_CDECL_END
#define UCNV_OPTION_SEP_CHAR ','
#define UCNV_OPTION_SEP_STRING ","
#define UCNV_VALUE_SEP_CHAR '='
#define UCNV_VALUE_SEP_STRING "="
#define UCNV_LOCALE_OPTION_STRING ",locale="
#define UCNV_VERSION_OPTION_STRING ",version="
#define UCNV_SWAP_LFNL_OPTION_STRING ",swaplfnl"
U_STABLE int U_EXPORT2
ucnv_compareNames(const char *name1, const char *name2);
U_STABLE UConverter* U_EXPORT2
ucnv_open(const char *converterName, UErrorCode *err);
U_STABLE UConverter* U_EXPORT2
ucnv_openU(const UChar *name,
           UErrorCode *err);
U_STABLE UConverter* U_EXPORT2
ucnv_openCCSID(int32_t codepage,
               UConverterPlatform platform,
               UErrorCode * err);
U_STABLE UConverter* U_EXPORT2
ucnv_openPackage(const char *packageName, const char *converterName, UErrorCode *err);
U_STABLE UConverter * U_EXPORT2
ucnv_safeClone(const UConverter *cnv,
               void             *stackBuffer,
               int32_t          *pBufferSize,
               UErrorCode       *status);
#define U_CNV_SAFECLONE_BUFFERSIZE  1024
U_STABLE void  U_EXPORT2
ucnv_close(UConverter * converter);
#if U_SHOW_CPLUSPLUS_API
U_NAMESPACE_BEGIN
U_DEFINE_LOCAL_OPEN_POINTER(LocalUConverterPointer, UConverter, ucnv_close);
U_NAMESPACE_END
#endif
U_STABLE void U_EXPORT2
ucnv_getSubstChars(const UConverter *converter,
                   char *subChars,
                   int8_t *len,
                   UErrorCode *err);
U_STABLE void U_EXPORT2
ucnv_setSubstChars(UConverter *converter,
                   const char *subChars,
                   int8_t len,
                   UErrorCode *err);
U_STABLE void U_EXPORT2
ucnv_setSubstString(UConverter *cnv,
                    const UChar *s,
                    int32_t length,
                    UErrorCode *err);
U_STABLE void U_EXPORT2
ucnv_getInvalidChars(const UConverter *converter,
                     char *errBytes,
                     int8_t *len,
                     UErrorCode *err);
U_STABLE void U_EXPORT2
ucnv_getInvalidUChars(const UConverter *converter,
                      UChar *errUChars,
                      int8_t *len,
                      UErrorCode *err);
U_STABLE void U_EXPORT2
ucnv_reset(UConverter *converter);
U_STABLE void U_EXPORT2
ucnv_resetToUnicode(UConverter *converter);
U_STABLE void U_EXPORT2
ucnv_resetFromUnicode(UConverter *converter);
U_STABLE int8_t U_EXPORT2
ucnv_getMaxCharSize(const UConverter *converter);
#define UCNV_GET_MAX_BYTES_FOR_STRING(length, maxCharSize) \
     (((int32_t)(length)+10)*(int32_t)(maxCharSize))
U_STABLE int8_t U_EXPORT2
ucnv_getMinCharSize(const UConverter *converter);
U_STABLE int32_t U_EXPORT2
ucnv_getDisplayName(const UConverter *converter,
                    const char *displayLocale,
                    UChar *displayName,
                    int32_t displayNameCapacity,
                    UErrorCode *err);
U_STABLE const char * U_EXPORT2
ucnv_getName(const UConverter *converter, UErrorCode *err);
U_STABLE int32_t U_EXPORT2
ucnv_getCCSID(const UConverter *converter,
              UErrorCode *err);
U_STABLE UConverterPlatform U_EXPORT2
ucnv_getPlatform(const UConverter *converter,
                 UErrorCode *err);
U_STABLE UConverterType U_EXPORT2
ucnv_getType(const UConverter * converter);
U_STABLE void U_EXPORT2
ucnv_getStarters(const UConverter* converter,
                 UBool starters[256],
                 UErrorCode* err);
typedef enum UConverterUnicodeSet {
    UCNV_ROUNDTRIP_SET,
    UCNV_ROUNDTRIP_AND_FALLBACK_SET,
    UCNV_SET_COUNT
} UConverterUnicodeSet;
U_STABLE void U_EXPORT2
ucnv_getUnicodeSet(const UConverter *cnv,
                   USet *setFillIn,
                   UConverterUnicodeSet whichSet,
                   UErrorCode *pErrorCode);
U_STABLE void U_EXPORT2
ucnv_getToUCallBack (const UConverter * converter,
                     UConverterToUCallback *action,
                     const void **context);
U_STABLE void U_EXPORT2
ucnv_getFromUCallBack (const UConverter * converter,
                       UConverterFromUCallback *action,
                       const void **context);
U_STABLE void U_EXPORT2
ucnv_setToUCallBack (UConverter * converter,
                     UConverterToUCallback newAction,
                     const void* newContext,
                     UConverterToUCallback *oldAction,
                     const void** oldContext,
                     UErrorCode * err);
U_STABLE void U_EXPORT2
ucnv_setFromUCallBack (UConverter * converter,
                       UConverterFromUCallback newAction,
                       const void *newContext,
                       UConverterFromUCallback *oldAction,
                       const void **oldContext,
                       UErrorCode * err);
U_STABLE void U_EXPORT2
ucnv_fromUnicode (UConverter * converter,
                  char **target,
                  const char *targetLimit,
                  const UChar ** source,
                  const UChar * sourceLimit,
                  int32_t* offsets,
                  UBool flush,
                  UErrorCode * err);
U_STABLE void U_EXPORT2
ucnv_toUnicode(UConverter *converter,
               UChar **target,
               const UChar *targetLimit,
               const char **source,
               const char *sourceLimit,
               int32_t *offsets,
               UBool flush,
               UErrorCode *err);
U_STABLE int32_t U_EXPORT2
ucnv_fromUChars(UConverter *cnv,
                char *dest, int32_t destCapacity,
                const UChar *src, int32_t srcLength,
                UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_toUChars(UConverter *cnv,
              UChar *dest, int32_t destCapacity,
              const char *src, int32_t srcLength,
              UErrorCode *pErrorCode);
U_STABLE UChar32 U_EXPORT2
ucnv_getNextUChar(UConverter * converter,
                  const char **source,
                  const char * sourceLimit,
                  UErrorCode * err);
U_STABLE void U_EXPORT2
ucnv_convertEx(UConverter *targetCnv, UConverter *sourceCnv,
               char **target, const char *targetLimit,
               const char **source, const char *sourceLimit,
               UChar *pivotStart, UChar **pivotSource,
               UChar **pivotTarget, const UChar *pivotLimit,
               UBool reset, UBool flush,
               UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_convert(const char *toConverterName,
             const char *fromConverterName,
             char *target,
             int32_t targetCapacity,
             const char *source,
             int32_t sourceLength,
             UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_toAlgorithmic(UConverterType algorithmicType,
                   UConverter *cnv,
                   char *target, int32_t targetCapacity,
                   const char *source, int32_t sourceLength,
                   UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_fromAlgorithmic(UConverter *cnv,
                     UConverterType algorithmicType,
                     char *target, int32_t targetCapacity,
                     const char *source, int32_t sourceLength,
                     UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_flushCache(void);
U_STABLE int32_t U_EXPORT2
ucnv_countAvailable(void);
U_STABLE const char* U_EXPORT2
ucnv_getAvailableName(int32_t n);
U_STABLE UEnumeration * U_EXPORT2
ucnv_openAllNames(UErrorCode *pErrorCode);
U_STABLE uint16_t U_EXPORT2
ucnv_countAliases(const char *alias, UErrorCode *pErrorCode);
U_STABLE const char * U_EXPORT2
ucnv_getAlias(const char *alias, uint16_t n, UErrorCode *pErrorCode);
U_STABLE void U_EXPORT2
ucnv_getAliases(const char *alias, const char **aliases, UErrorCode *pErrorCode);
U_STABLE UEnumeration * U_EXPORT2
ucnv_openStandardNames(const char *convName,
                       const char *standard,
                       UErrorCode *pErrorCode);
U_STABLE uint16_t U_EXPORT2
ucnv_countStandards(void);
U_STABLE const char * U_EXPORT2
ucnv_getStandard(uint16_t n, UErrorCode *pErrorCode);
U_STABLE const char * U_EXPORT2
ucnv_getStandardName(const char *name, const char *standard, UErrorCode *pErrorCode);
U_STABLE const char * U_EXPORT2
ucnv_getCanonicalName(const char *alias, const char *standard, UErrorCode *pErrorCode);
U_STABLE const char * U_EXPORT2
ucnv_getDefaultName(void);
U_STABLE void U_EXPORT2
ucnv_setDefaultName(const char *name);
U_STABLE void U_EXPORT2
ucnv_fixFileSeparator(const UConverter *cnv, UChar *source, int32_t sourceLen);
U_STABLE UBool U_EXPORT2
ucnv_isAmbiguous(const UConverter *cnv);
U_STABLE void U_EXPORT2
ucnv_setFallback(UConverter *cnv, UBool usesFallback);
U_STABLE UBool U_EXPORT2
ucnv_usesFallback(const UConverter *cnv);
U_STABLE const char* U_EXPORT2
ucnv_detectUnicodeSignature(const char* source,
                            int32_t sourceLength,
                            int32_t *signatureLength,
                            UErrorCode *pErrorCode);
U_STABLE int32_t U_EXPORT2
ucnv_fromUCountPending(const UConverter* cnv, UErrorCode* status);
U_STABLE int32_t U_EXPORT2
ucnv_toUCountPending(const UConverter* cnv, UErrorCode* status);
#endif
#endif
