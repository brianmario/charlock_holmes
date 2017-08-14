#ifndef REP_H
#define REP_H
#include "unicode/uobject.h"
U_NAMESPACE_BEGIN
class UnicodeString;
class U_COMMON_API Replaceable : public UObject {
public:
    virtual ~Replaceable();
    inline int32_t length() const;
    inline UChar charAt(int32_t offset) const;
    inline UChar32 char32At(int32_t offset) const;
    virtual void extractBetween(int32_t start,
                                int32_t limit,
                                UnicodeString& target) const = 0;
    virtual void handleReplaceBetween(int32_t start,
                                      int32_t limit,
                                      const UnicodeString& text) = 0;
    virtual void copy(int32_t start, int32_t limit, int32_t dest) = 0;
    virtual UBool hasMetaData() const;
    virtual Replaceable *clone() const;
protected:
    Replaceable();
    virtual int32_t getLength() const = 0;
    virtual UChar getCharAt(int32_t offset) const = 0;
    virtual UChar32 getChar32At(int32_t offset) const = 0;
};
inline int32_t
Replaceable::length() const {
    return getLength();
}
inline UChar
Replaceable::charAt(int32_t offset) const {
    return getCharAt(offset);
}
inline UChar32
Replaceable::char32At(int32_t offset) const {
    return getChar32At(offset);
}
U_NAMESPACE_END
#endif
