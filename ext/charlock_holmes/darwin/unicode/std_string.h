#ifndef __STD_STRING_H__
#define __STD_STRING_H__
#include "unicode/utypes.h"
#ifndef U_HAVE_STD_STRING
#define U_HAVE_STD_STRING 1
#endif
#if U_HAVE_STD_STRING
#include <string>
#ifndef U_STD_NSQ
#   if U_HAVE_NAMESPACE
#       define U_STD_NS std
#       define U_STD_NSQ U_STD_NS::
#       define U_STD_NS_USE using namespace U_STD_NS;
#   else
#       define U_STD_NS
#       define U_STD_NSQ
#       define U_STD_NS_USE
#   endif
#endif
#endif
#endif
