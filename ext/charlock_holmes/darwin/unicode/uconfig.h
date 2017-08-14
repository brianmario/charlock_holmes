#ifndef __UCONFIG_H__
#define __UCONFIG_H__
#if defined(UCONFIG_USE_LOCAL)
#include "uconfig_local.h"
#endif
#ifndef UCONFIG_ONLY_COLLATION
#   define UCONFIG_ONLY_COLLATION 0
#endif
#if UCONFIG_ONLY_COLLATION
#   define UCONFIG_NO_BREAK_ITERATION 1
#   define UCONFIG_NO_IDNA 1
#   if UCONFIG_NO_COLLATION
#       error Contradictory collation switches in uconfig.h.
#   endif
#   define UCONFIG_NO_FORMATTING 1
#   define UCONFIG_NO_TRANSLITERATION 1
#   define UCONFIG_NO_REGULAR_EXPRESSIONS 1
#endif
#ifndef UCONFIG_NO_FILE_IO
#   define UCONFIG_NO_FILE_IO 0
#endif
#ifndef UCONFIG_NO_CONVERSION
#   define UCONFIG_NO_CONVERSION 0
#endif
#if UCONFIG_NO_CONVERSION
#   define UCONFIG_NO_LEGACY_CONVERSION 1
#endif
#ifndef UCONFIG_NO_LEGACY_CONVERSION
#   define UCONFIG_NO_LEGACY_CONVERSION 0
#endif
#ifndef UCONFIG_NO_NORMALIZATION
#   define UCONFIG_NO_NORMALIZATION 0
#elif UCONFIG_NO_NORMALIZATION
#   define UCONFIG_NO_IDNA 1
#   if UCONFIG_ONLY_COLLATION
#       error Contradictory collation switches in uconfig.h.
#   endif
#   define UCONFIG_NO_COLLATION 1
#   define UCONFIG_NO_TRANSLITERATION 1
#endif
#ifndef UCONFIG_NO_BREAK_ITERATION
#   define UCONFIG_NO_BREAK_ITERATION 0
#endif
#ifndef UCONFIG_NO_IDNA
#   define UCONFIG_NO_IDNA 0
#endif
#ifndef UCONFIG_NO_COLLATION
#   define UCONFIG_NO_COLLATION 0
#endif
#ifndef UCONFIG_NO_FORMATTING
#   define UCONFIG_NO_FORMATTING 0
#endif
#ifndef UCONFIG_NO_TRANSLITERATION
#   define UCONFIG_NO_TRANSLITERATION 0
#endif
#ifndef UCONFIG_NO_REGULAR_EXPRESSIONS
#   define UCONFIG_NO_REGULAR_EXPRESSIONS 0
#endif
#ifndef UCONFIG_NO_SERVICE
#   define UCONFIG_NO_SERVICE 1
#endif
#endif
