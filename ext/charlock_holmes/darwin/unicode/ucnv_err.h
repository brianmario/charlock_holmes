#ifndef UCNV_ERR_H
#define UCNV_ERR_H
#include "unicode/utypes.h"
#if !UCONFIG_NO_CONVERSION
struct UConverter;
typedef struct UConverter UConverter;
#define UCNV_SUB_STOP_ON_ILLEGAL "i"
#define UCNV_SKIP_STOP_ON_ILLEGAL "i"
#define UCNV_ESCAPE_ICU       NULL
#define UCNV_ESCAPE_JAVA      "J"
#define UCNV_ESCAPE_C         "C"
#define UCNV_ESCAPE_XML_DEC   "D"
#define UCNV_ESCAPE_XML_HEX   "X"
#define UCNV_ESCAPE_UNICODE   "U"
#define UCNV_ESCAPE_CSS2   "S"
typedef enum {
    UCNV_UNASSIGNED = 0,
    UCNV_ILLEGAL = 1,
    UCNV_IRREGULAR = 2,
    UCNV_RESET = 3,
    UCNV_CLOSE = 4,
    UCNV_CLONE = 5
} UConverterCallbackReason;
typedef struct {
    uint16_t size;
    UBool flush;
    UConverter *converter;
    const UChar *source;
    const UChar *sourceLimit;
    char *target;
    const char *targetLimit;
    int32_t *offsets;
} UConverterFromUnicodeArgs;
typedef struct {
    uint16_t size;
    UBool flush;
    UConverter *converter;
    const char *source;
    const char *sourceLimit;
    UChar *target;
    const UChar *targetLimit;
    int32_t *offsets;
} UConverterToUnicodeArgs;
U_STABLE void U_EXPORT2 UCNV_FROM_U_CALLBACK_STOP (
                  const void *context,
                  UConverterFromUnicodeArgs *fromUArgs,
                  const UChar* codeUnits,
                  int32_t length,
                  UChar32 codePoint,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_TO_U_CALLBACK_STOP (
                  const void *context,
                  UConverterToUnicodeArgs *toUArgs,
                  const char* codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_FROM_U_CALLBACK_SKIP (
                  const void *context,
                  UConverterFromUnicodeArgs *fromUArgs,
                  const UChar* codeUnits,
                  int32_t length,
                  UChar32 codePoint,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_FROM_U_CALLBACK_SUBSTITUTE (
                  const void *context,
                  UConverterFromUnicodeArgs *fromUArgs,
                  const UChar* codeUnits,
                  int32_t length,
                  UChar32 codePoint,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_FROM_U_CALLBACK_ESCAPE (
                  const void *context,
                  UConverterFromUnicodeArgs *fromUArgs,
                  const UChar* codeUnits,
                  int32_t length,
                  UChar32 codePoint,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_TO_U_CALLBACK_SKIP (
                  const void *context,
                  UConverterToUnicodeArgs *toUArgs,
                  const char* codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_TO_U_CALLBACK_SUBSTITUTE (
                  const void *context,
                  UConverterToUnicodeArgs *toUArgs,
                  const char* codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
U_STABLE void U_EXPORT2 UCNV_TO_U_CALLBACK_ESCAPE (
                  const void *context,
                  UConverterToUnicodeArgs *toUArgs,
                  const char* codeUnits,
                  int32_t length,
                  UConverterCallbackReason reason,
                  UErrorCode * err);
#endif
#endif
