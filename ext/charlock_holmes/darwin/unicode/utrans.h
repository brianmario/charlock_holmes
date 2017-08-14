#ifndef UTRANS_H
#define UTRANS_H
#include "unicode/utypes.h"
#if !UCONFIG_NO_TRANSLITERATION
#include "unicode/localpointer.h"
#include "unicode/urep.h"
#include "unicode/parseerr.h"
#include "unicode/uenum.h"
typedef void* UTransliterator;
typedef enum UTransDirection {
    UTRANS_FORWARD,
    UTRANS_REVERSE
} UTransDirection;
typedef struct UTransPosition {
    int32_t contextStart;
    int32_t contextLimit;
    int32_t start;
    int32_t limit;
} UTransPosition;
U_STABLE UTransliterator* U_EXPORT2
utrans_openU(const UChar *id,
             int32_t idLength,
             UTransDirection dir,
             const UChar *rules,
             int32_t rulesLength,
             UParseError *parseError,
             UErrorCode *pErrorCode);
U_STABLE UTransliterator* U_EXPORT2
utrans_openInverse(const UTransliterator* trans,
                   UErrorCode* status);
U_STABLE UTransliterator* U_EXPORT2
utrans_clone(const UTransliterator* trans,
             UErrorCode* status);
U_STABLE void U_EXPORT2
utrans_close(UTransliterator* trans);
#if U_SHOW_CPLUSPLUS_API
U_NAMESPACE_BEGIN
U_DEFINE_LOCAL_OPEN_POINTER(LocalUTransliteratorPointer, UTransliterator, utrans_close);
U_NAMESPACE_END
#endif
U_STABLE const UChar * U_EXPORT2
utrans_getUnicodeID(const UTransliterator *trans,
                    int32_t *resultLength);
U_STABLE void U_EXPORT2
utrans_register(UTransliterator* adoptedTrans,
                UErrorCode* status);
U_STABLE void U_EXPORT2
utrans_unregisterID(const UChar* id, int32_t idLength);
U_STABLE void U_EXPORT2
utrans_setFilter(UTransliterator* trans,
                 const UChar* filterPattern,
                 int32_t filterPatternLen,
                 UErrorCode* status);
U_STABLE int32_t U_EXPORT2
utrans_countAvailableIDs(void);
U_STABLE UEnumeration * U_EXPORT2
utrans_openIDs(UErrorCode *pErrorCode);
U_STABLE void U_EXPORT2
utrans_trans(const UTransliterator* trans,
             UReplaceable* rep,
             UReplaceableCallbacks* repFunc,
             int32_t start,
             int32_t* limit,
             UErrorCode* status);
U_STABLE void U_EXPORT2
utrans_transIncremental(const UTransliterator* trans,
                        UReplaceable* rep,
                        UReplaceableCallbacks* repFunc,
                        UTransPosition* pos,
                        UErrorCode* status);
U_STABLE void U_EXPORT2
utrans_transUChars(const UTransliterator* trans,
                   UChar* text,
                   int32_t* textLength,
                   int32_t textCapacity,
                   int32_t start,
                   int32_t* limit,
                   UErrorCode* status);
U_STABLE void U_EXPORT2
utrans_transIncrementalUChars(const UTransliterator* trans,
                              UChar* text,
                              int32_t* textLength,
                              int32_t textCapacity,
                              UTransPosition* pos,
                              UErrorCode* status);
U_DEPRECATED UTransliterator* U_EXPORT2
utrans_open(const char* id,
            UTransDirection dir,
            const UChar* rules,
            int32_t rulesLength,
            UParseError* parseError,
            UErrorCode* status);
U_DEPRECATED int32_t U_EXPORT2
utrans_getID(const UTransliterator* trans,
             char* buf,
             int32_t bufCapacity);
U_DEPRECATED void U_EXPORT2
utrans_unregister(const char* id);
U_DEPRECATED int32_t U_EXPORT2
utrans_getAvailableID(int32_t index,
                      char* buf,
                      int32_t bufCapacity);
#endif
#endif
