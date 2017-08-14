#ifndef PARSEERR_H
#define PARSEERR_H
#include "unicode/utypes.h"
enum { U_PARSE_CONTEXT_LEN = 16 };
typedef struct UParseError {
    int32_t        line;
    int32_t        offset;
    UChar          preContext[U_PARSE_CONTEXT_LEN];
    UChar          postContext[U_PARSE_CONTEXT_LEN];
} UParseError;
#endif
