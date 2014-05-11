#ifndef STRENUM_H
#define STRENUM_H
#include "unicode/uobject.h"
#include "unicode/unistr.h"
U_NAMESPACE_BEGIN
class U_COMMON_API StringEnumeration : public UObject {
public:
    virtual ~StringEnumeration();
    virtual StringEnumeration *clone() const;
    virtual int32_t count(UErrorCode& status) const = 0;
    virtual const char* next(int32_t *resultLength, UErrorCode& status);
    virtual const UChar* unext(int32_t *resultLength, UErrorCode& status);
    virtual const UnicodeString* snext(UErrorCode& status) = 0;
    virtual void reset(UErrorCode& status) = 0;
    virtual UBool operator==(const StringEnumeration& that)const;
    virtual UBool operator!=(const StringEnumeration& that)const;
protected:
    UnicodeString unistr;
    char charsBuffer[32];
    char *chars;
    int32_t charsCapacity;
    StringEnumeration();
    void ensureCharsCapacity(int32_t capacity, UErrorCode &status);
    UnicodeString *setChars(const char *s, int32_t length, UErrorCode &status);
};
U_NAMESPACE_END
#endif
