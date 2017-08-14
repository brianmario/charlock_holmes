#ifndef __UREP_H
#define __UREP_H
#include "unicode/utypes.h"
U_CDECL_BEGIN
typedef void* UReplaceable;
typedef struct UReplaceableCallbacks {
    int32_t (*length)(const UReplaceable* rep);
    UChar   (*charAt)(const UReplaceable* rep,
                      int32_t offset);
    UChar32 (*char32At)(const UReplaceable* rep,
                        int32_t offset);
    void    (*replace)(UReplaceable* rep,
                       int32_t start,
                       int32_t limit,
                       const UChar* text,
                       int32_t textLength);
    void    (*extract)(UReplaceable* rep,
                       int32_t start,
                       int32_t limit,
                       UChar* dst);
    void    (*copy)(UReplaceable* rep,
                    int32_t start,
                    int32_t limit,
                    int32_t dest);
} UReplaceableCallbacks;
U_CDECL_END
#endif
