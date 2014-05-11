#ifndef UNISTR_H
#define UNISTR_H
#include "unicode/utypes.h"
#include "unicode/rep.h"
#include "unicode/std_string.h"
#include "unicode/stringpiece.h"
#include "unicode/bytestream.h"
struct UConverter;
class  StringThreadTest;
#ifndef U_COMPARE_CODE_POINT_ORDER
#define U_COMPARE_CODE_POINT_ORDER  0x8000
#endif
#ifndef USTRING_H
U_STABLE int32_t U_EXPORT2
u_strlen(const UChar *s);
#endif
U_NAMESPACE_BEGIN
class Locale;
class StringCharacterIterator;
class BreakIterator;
#define US_INV U_NAMESPACE_QUALIFIER UnicodeString::kInvariant
#if defined(U_DECLARE_UTF16)
#   define UNICODE_STRING(cs, _length) U_NAMESPACE_QUALIFIER UnicodeString(TRUE, (const UChar *)U_DECLARE_UTF16(cs), _length)
#elif U_SIZEOF_WCHAR_T==U_SIZEOF_UCHAR && (U_CHARSET_FAMILY==U_ASCII_FAMILY || (U_SIZEOF_UCHAR == 2 && defined(U_WCHAR_IS_UTF16)))
#   define UNICODE_STRING(cs, _length) U_NAMESPACE_QUALIFIER UnicodeString(TRUE, (const UChar *)L ## cs, _length)
#elif U_SIZEOF_UCHAR==1 && U_CHARSET_FAMILY==U_ASCII_FAMILY
#   define UNICODE_STRING(cs, _length) U_NAMESPACE_QUALIFIER UnicodeString(TRUE, (const UChar *)cs, _length)
#else
#   define UNICODE_STRING(cs, _length) U_NAMESPACE_QUALIFIER UnicodeString(cs, _length, US_INV)
#endif
#define UNICODE_STRING_SIMPLE(cs) UNICODE_STRING(cs, -1)
class U_COMMON_API UnicodeString : public Replaceable
{
public:
  enum EInvariant {
    kInvariant
  };
  inline UBool operator== (const UnicodeString& text) const;
  inline UBool operator!= (const UnicodeString& text) const;
  inline UBool operator> (const UnicodeString& text) const;
  inline UBool operator< (const UnicodeString& text) const;
  inline UBool operator>= (const UnicodeString& text) const;
  inline UBool operator<= (const UnicodeString& text) const;
  inline int8_t compare(const UnicodeString& text) const;
  inline int8_t compare(int32_t start,
         int32_t length,
         const UnicodeString& text) const;
   inline int8_t compare(int32_t start,
         int32_t length,
         const UnicodeString& srcText,
         int32_t srcStart,
         int32_t srcLength) const;
  inline int8_t compare(const UChar *srcChars,
         int32_t srcLength) const;
  inline int8_t compare(int32_t start,
         int32_t length,
         const UChar *srcChars) const;
  inline int8_t compare(int32_t start,
         int32_t length,
         const UChar *srcChars,
         int32_t srcStart,
         int32_t srcLength) const;
  inline int8_t compareBetween(int32_t start,
            int32_t limit,
            const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLimit) const;
  inline int8_t compareCodePointOrder(const UnicodeString& text) const;
  inline int8_t compareCodePointOrder(int32_t start,
                                      int32_t length,
                                      const UnicodeString& srcText) const;
   inline int8_t compareCodePointOrder(int32_t start,
                                       int32_t length,
                                       const UnicodeString& srcText,
                                       int32_t srcStart,
                                       int32_t srcLength) const;
  inline int8_t compareCodePointOrder(const UChar *srcChars,
                                      int32_t srcLength) const;
  inline int8_t compareCodePointOrder(int32_t start,
                                      int32_t length,
                                      const UChar *srcChars) const;
  inline int8_t compareCodePointOrder(int32_t start,
                                      int32_t length,
                                      const UChar *srcChars,
                                      int32_t srcStart,
                                      int32_t srcLength) const;
  inline int8_t compareCodePointOrderBetween(int32_t start,
                                             int32_t limit,
                                             const UnicodeString& srcText,
                                             int32_t srcStart,
                                             int32_t srcLimit) const;
  inline int8_t caseCompare(const UnicodeString& text, uint32_t options) const;
  inline int8_t caseCompare(int32_t start,
         int32_t length,
         const UnicodeString& srcText,
         uint32_t options) const;
  inline int8_t caseCompare(int32_t start,
         int32_t length,
         const UnicodeString& srcText,
         int32_t srcStart,
         int32_t srcLength,
         uint32_t options) const;
  inline int8_t caseCompare(const UChar *srcChars,
         int32_t srcLength,
         uint32_t options) const;
  inline int8_t caseCompare(int32_t start,
         int32_t length,
         const UChar *srcChars,
         uint32_t options) const;
  inline int8_t caseCompare(int32_t start,
         int32_t length,
         const UChar *srcChars,
         int32_t srcStart,
         int32_t srcLength,
         uint32_t options) const;
  inline int8_t caseCompareBetween(int32_t start,
            int32_t limit,
            const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLimit,
            uint32_t options) const;
  inline UBool startsWith(const UnicodeString& text) const;
  inline UBool startsWith(const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLength) const;
  inline UBool startsWith(const UChar *srcChars,
            int32_t srcLength) const;
  inline UBool startsWith(const UChar *srcChars,
            int32_t srcStart,
            int32_t srcLength) const;
  inline UBool endsWith(const UnicodeString& text) const;
  inline UBool endsWith(const UnicodeString& srcText,
          int32_t srcStart,
          int32_t srcLength) const;
  inline UBool endsWith(const UChar *srcChars,
          int32_t srcLength) const;
  inline UBool endsWith(const UChar *srcChars,
          int32_t srcStart,
          int32_t srcLength) const;
  inline int32_t indexOf(const UnicodeString& text) const;
  inline int32_t indexOf(const UnicodeString& text,
              int32_t start) const;
  inline int32_t indexOf(const UnicodeString& text,
              int32_t start,
              int32_t length) const;
  inline int32_t indexOf(const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  inline int32_t indexOf(const UChar *srcChars,
              int32_t srcLength,
              int32_t start) const;
  inline int32_t indexOf(const UChar *srcChars,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  int32_t indexOf(const UChar *srcChars,
              int32_t srcStart,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  inline int32_t indexOf(UChar c) const;
  inline int32_t indexOf(UChar32 c) const;
  inline int32_t indexOf(UChar c,
              int32_t start) const;
  inline int32_t indexOf(UChar32 c,
              int32_t start) const;
  inline int32_t indexOf(UChar c,
              int32_t start,
              int32_t length) const;
  inline int32_t indexOf(UChar32 c,
              int32_t start,
              int32_t length) const;
  inline int32_t lastIndexOf(const UnicodeString& text) const;
  inline int32_t lastIndexOf(const UnicodeString& text,
              int32_t start) const;
  inline int32_t lastIndexOf(const UnicodeString& text,
              int32_t start,
              int32_t length) const;
  inline int32_t lastIndexOf(const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  inline int32_t lastIndexOf(const UChar *srcChars,
              int32_t srcLength,
              int32_t start) const;
  inline int32_t lastIndexOf(const UChar *srcChars,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  int32_t lastIndexOf(const UChar *srcChars,
              int32_t srcStart,
              int32_t srcLength,
              int32_t start,
              int32_t length) const;
  inline int32_t lastIndexOf(UChar c) const;
  inline int32_t lastIndexOf(UChar32 c) const;
  inline int32_t lastIndexOf(UChar c,
              int32_t start) const;
  inline int32_t lastIndexOf(UChar32 c,
              int32_t start) const;
  inline int32_t lastIndexOf(UChar c,
              int32_t start,
              int32_t length) const;
  inline int32_t lastIndexOf(UChar32 c,
              int32_t start,
              int32_t length) const;
  inline UChar charAt(int32_t offset) const;
  inline UChar operator[] (int32_t offset) const;
  inline UChar32 char32At(int32_t offset) const;
  inline int32_t getChar32Start(int32_t offset) const;
  inline int32_t getChar32Limit(int32_t offset) const;
  int32_t moveIndex32(int32_t index, int32_t delta) const;
  inline void extract(int32_t start,
           int32_t length,
           UChar *dst,
           int32_t dstStart = 0) const;
  int32_t
  extract(UChar *dest, int32_t destCapacity,
          UErrorCode &errorCode) const;
  inline void extract(int32_t start,
           int32_t length,
           UnicodeString& target) const;
  inline void extractBetween(int32_t start,
              int32_t limit,
              UChar *dst,
              int32_t dstStart = 0) const;
  virtual void extractBetween(int32_t start,
              int32_t limit,
              UnicodeString& target) const;
  int32_t extract(int32_t start,
           int32_t startLength,
           char *target,
           int32_t targetCapacity,
           enum EInvariant inv) const;
#if U_CHARSET_IS_UTF8 || !UCONFIG_NO_CONVERSION
  int32_t extract(int32_t start,
           int32_t startLength,
           char *target,
           uint32_t targetLength) const;
#endif
#if !UCONFIG_NO_CONVERSION
  inline int32_t extract(int32_t start,
                 int32_t startLength,
                 char *target,
                 const char *codepage = 0) const;
  int32_t extract(int32_t start,
           int32_t startLength,
           char *target,
           uint32_t targetLength,
           const char *codepage) const;
  int32_t extract(char *dest, int32_t destCapacity,
                  UConverter *cnv,
                  UErrorCode &errorCode) const;
#endif
  UnicodeString tempSubString(int32_t start=0, int32_t length=INT32_MAX) const;
  inline UnicodeString tempSubStringBetween(int32_t start, int32_t limit=INT32_MAX) const;
  void toUTF8(ByteSink &sink) const;
#if U_HAVE_STD_STRING
  template<typename StringClass>
  StringClass &toUTF8String(StringClass &result) const {
    StringByteSink<StringClass> sbs(&result);
    toUTF8(sbs);
    return result;
  }
#endif
  int32_t toUTF32(UChar32 *utf32, int32_t capacity, UErrorCode &errorCode) const;
  inline int32_t length(void) const;
  int32_t
  countChar32(int32_t start=0, int32_t length=INT32_MAX) const;
  UBool
  hasMoreChar32Than(int32_t start, int32_t length, int32_t number) const;
  inline UBool isEmpty(void) const;
  inline int32_t getCapacity(void) const;
  inline int32_t hashCode(void) const;
  inline UBool isBogus(void) const;
  UnicodeString &operator=(const UnicodeString &srcText);
  UnicodeString &fastCopyFrom(const UnicodeString &src);
  inline UnicodeString& operator= (UChar ch);
  inline UnicodeString& operator= (UChar32 ch);
  inline UnicodeString& setTo(const UnicodeString& srcText,
               int32_t srcStart);
  inline UnicodeString& setTo(const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength);
  inline UnicodeString& setTo(const UnicodeString& srcText);
  inline UnicodeString& setTo(const UChar *srcChars,
               int32_t srcLength);
  UnicodeString& setTo(UChar srcChar);
  UnicodeString& setTo(UChar32 srcChar);
  UnicodeString &setTo(UBool isTerminated,
                       const UChar *text,
                       int32_t textLength);
  UnicodeString &setTo(UChar *buffer,
                       int32_t buffLength,
                       int32_t buffCapacity);
  void setToBogus();
  UnicodeString& setCharAt(int32_t offset,
               UChar ch);
 inline  UnicodeString& operator+= (UChar ch);
 inline  UnicodeString& operator+= (UChar32 ch);
  inline UnicodeString& operator+= (const UnicodeString& srcText);
  inline UnicodeString& append(const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLength);
  inline UnicodeString& append(const UnicodeString& srcText);
  inline UnicodeString& append(const UChar *srcChars,
            int32_t srcStart,
            int32_t srcLength);
  inline UnicodeString& append(const UChar *srcChars,
            int32_t srcLength);
  inline UnicodeString& append(UChar srcChar);
  inline UnicodeString& append(UChar32 srcChar);
  inline UnicodeString& insert(int32_t start,
            const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLength);
  inline UnicodeString& insert(int32_t start,
            const UnicodeString& srcText);
  inline UnicodeString& insert(int32_t start,
            const UChar *srcChars,
            int32_t srcStart,
            int32_t srcLength);
  inline UnicodeString& insert(int32_t start,
            const UChar *srcChars,
            int32_t srcLength);
  inline UnicodeString& insert(int32_t start,
            UChar srcChar);
  inline UnicodeString& insert(int32_t start,
            UChar32 srcChar);
  UnicodeString& replace(int32_t start,
             int32_t length,
             const UnicodeString& srcText,
             int32_t srcStart,
             int32_t srcLength);
  UnicodeString& replace(int32_t start,
             int32_t length,
             const UnicodeString& srcText);
  UnicodeString& replace(int32_t start,
             int32_t length,
             const UChar *srcChars,
             int32_t srcStart,
             int32_t srcLength);
  inline UnicodeString& replace(int32_t start,
             int32_t length,
             const UChar *srcChars,
             int32_t srcLength);
  inline UnicodeString& replace(int32_t start,
             int32_t length,
             UChar srcChar);
  inline UnicodeString& replace(int32_t start,
             int32_t length,
             UChar32 srcChar);
  inline UnicodeString& replaceBetween(int32_t start,
                int32_t limit,
                const UnicodeString& srcText);
  inline UnicodeString& replaceBetween(int32_t start,
                int32_t limit,
                const UnicodeString& srcText,
                int32_t srcStart,
                int32_t srcLimit);
  virtual void handleReplaceBetween(int32_t start,
                                    int32_t limit,
                                    const UnicodeString& text);
  virtual UBool hasMetaData() const;
  virtual void copy(int32_t start, int32_t limit, int32_t dest);
  inline UnicodeString& findAndReplace(const UnicodeString& oldText,
                const UnicodeString& newText);
  inline UnicodeString& findAndReplace(int32_t start,
                int32_t length,
                const UnicodeString& oldText,
                const UnicodeString& newText);
  UnicodeString& findAndReplace(int32_t start,
                int32_t length,
                const UnicodeString& oldText,
                int32_t oldStart,
                int32_t oldLength,
                const UnicodeString& newText,
                int32_t newStart,
                int32_t newLength);
  inline UnicodeString& remove(void);
  inline UnicodeString& remove(int32_t start,
                               int32_t length = (int32_t)INT32_MAX);
  inline UnicodeString& removeBetween(int32_t start,
                                      int32_t limit = (int32_t)INT32_MAX);
  inline UnicodeString &retainBetween(int32_t start, int32_t limit = INT32_MAX);
  UBool padLeading(int32_t targetLength,
                    UChar padChar = 0x0020);
  UBool padTrailing(int32_t targetLength,
                     UChar padChar = 0x0020);
  inline UBool truncate(int32_t targetLength);
  UnicodeString& trim(void);
  inline UnicodeString& reverse(void);
  inline UnicodeString& reverse(int32_t start,
             int32_t length);
  UnicodeString& toUpper(void);
  UnicodeString& toUpper(const Locale& locale);
  UnicodeString& toLower(void);
  UnicodeString& toLower(const Locale& locale);
#if !UCONFIG_NO_BREAK_ITERATION
  UnicodeString &toTitle(BreakIterator *titleIter);
  UnicodeString &toTitle(BreakIterator *titleIter, const Locale &locale);
  UnicodeString &toTitle(BreakIterator *titleIter, const Locale &locale, uint32_t options);
#endif
  UnicodeString &foldCase(uint32_t options=0 );
  UChar *getBuffer(int32_t minCapacity);
  void releaseBuffer(int32_t newLength=-1);
  inline const UChar *getBuffer() const;
  inline const UChar *getTerminatedBuffer();
  UnicodeString();
  UnicodeString(int32_t capacity, UChar32 c, int32_t count);
  UnicodeString(UChar ch);
  UnicodeString(UChar32 ch);
  UnicodeString(const UChar *text);
  UnicodeString(const UChar *text,
        int32_t textLength);
  UnicodeString(UBool isTerminated,
                const UChar *text,
                int32_t textLength);
  UnicodeString(UChar *buffer, int32_t buffLength, int32_t buffCapacity);
#if U_CHARSET_IS_UTF8 || !UCONFIG_NO_CONVERSION
  UnicodeString(const char *codepageData);
  UnicodeString(const char *codepageData, int32_t dataLength);
#endif
#if !UCONFIG_NO_CONVERSION
  UnicodeString(const char *codepageData, const char *codepage);
  UnicodeString(const char *codepageData, int32_t dataLength, const char *codepage);
  UnicodeString(
        const char *src, int32_t srcLength,
        UConverter *cnv,
        UErrorCode &errorCode);
#endif
  UnicodeString(const char *src, int32_t length, enum EInvariant inv);
  UnicodeString(const UnicodeString& that);
  UnicodeString(const UnicodeString& src, int32_t srcStart);
  UnicodeString(const UnicodeString& src, int32_t srcStart, int32_t srcLength);
  virtual Replaceable *clone() const;
  virtual ~UnicodeString();
  static UnicodeString fromUTF8(const StringPiece &utf8);
  static UnicodeString fromUTF32(const UChar32 *utf32, int32_t length);
  UnicodeString unescape() const;
  UChar32 unescapeAt(int32_t &offset) const;
  static UClassID U_EXPORT2 getStaticClassID();
  virtual UClassID getDynamicClassID() const;
protected:
  virtual int32_t getLength() const;
  virtual UChar getCharAt(int32_t offset) const;
  virtual UChar32 getChar32At(int32_t offset) const;
private:
  UnicodeString &setToUTF8(const StringPiece &utf8);
  int32_t
  toUTF8(int32_t start, int32_t len,
         char *target, int32_t capacity) const;
  inline int8_t
  doCompare(int32_t start,
           int32_t length,
           const UnicodeString& srcText,
           int32_t srcStart,
           int32_t srcLength) const;
  int8_t doCompare(int32_t start,
           int32_t length,
           const UChar *srcChars,
           int32_t srcStart,
           int32_t srcLength) const;
  inline int8_t
  doCompareCodePointOrder(int32_t start,
                          int32_t length,
                          const UnicodeString& srcText,
                          int32_t srcStart,
                          int32_t srcLength) const;
  int8_t doCompareCodePointOrder(int32_t start,
                                 int32_t length,
                                 const UChar *srcChars,
                                 int32_t srcStart,
                                 int32_t srcLength) const;
  inline int8_t
  doCaseCompare(int32_t start,
                int32_t length,
                const UnicodeString &srcText,
                int32_t srcStart,
                int32_t srcLength,
                uint32_t options) const;
  int8_t
  doCaseCompare(int32_t start,
                int32_t length,
                const UChar *srcChars,
                int32_t srcStart,
                int32_t srcLength,
                uint32_t options) const;
  int32_t doIndexOf(UChar c,
            int32_t start,
            int32_t length) const;
  int32_t doIndexOf(UChar32 c,
                        int32_t start,
                        int32_t length) const;
  int32_t doLastIndexOf(UChar c,
                int32_t start,
                int32_t length) const;
  int32_t doLastIndexOf(UChar32 c,
                            int32_t start,
                            int32_t length) const;
  void doExtract(int32_t start,
         int32_t length,
         UChar *dst,
         int32_t dstStart) const;
  inline void doExtract(int32_t start,
         int32_t length,
         UnicodeString& target) const;
  inline UChar doCharAt(int32_t offset)  const;
  UnicodeString& doReplace(int32_t start,
               int32_t length,
               const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength);
  UnicodeString& doReplace(int32_t start,
               int32_t length,
               const UChar *srcChars,
               int32_t srcStart,
               int32_t srcLength);
  UnicodeString& doReverse(int32_t start,
               int32_t length);
  int32_t doHashCode(void) const;
  inline UChar* getArrayStart(void);
  inline const UChar* getArrayStart(void) const;
  inline UBool isWritable() const;
  inline UBool isBufferWritable() const;
  inline void setLength(int32_t len);
  inline void setToEmpty();
  inline void setArray(UChar *array, int32_t len, int32_t capacity);
  UBool allocate(int32_t capacity);
  void releaseArray(void);
  void unBogus();
  UnicodeString &copyFrom(const UnicodeString &src, UBool fastCopy=FALSE);
  inline void pinIndex(int32_t& start) const;
  inline void pinIndices(int32_t& start,
                         int32_t& length) const;
#if !UCONFIG_NO_CONVERSION
  int32_t doExtract(int32_t start, int32_t length,
                    char *dest, int32_t destCapacity,
                    UConverter *cnv,
                    UErrorCode &errorCode) const;
  void doCodepageCreate(const char *codepageData,
                        int32_t dataLength,
                        const char *codepage);
  void
  doCodepageCreate(const char *codepageData,
                   int32_t dataLength,
                   UConverter *converter,
                   UErrorCode &status);
#endif
  UBool cloneArrayIfNeeded(int32_t newCapacity = -1,
                            int32_t growCapacity = -1,
                            UBool doCopyArray = TRUE,
                            int32_t **pBufferToDelete = 0,
                            UBool forceClone = FALSE);
  UnicodeString &
  caseMap(BreakIterator *titleIter,
          const char *locale,
          uint32_t options,
          int32_t toWhichCase);
  void addRef(void);
  int32_t removeRef(void);
  int32_t refCount(void) const;
  enum {
    US_STACKBUF_SIZE= sizeof(void *)==4 ? 13 : 15,
    kInvalidUChar=0xffff,
    kGrowSize=128,
    kInvalidHashCode=0,
    kEmptyHashCode=1,
    kIsBogus=1,
    kUsingStackBuffer=2,
    kRefCounted=4,
    kBufferIsReadonly=8,
    kOpenGetBuffer=16,
    kShortString=kUsingStackBuffer,
    kLongString=kRefCounted,
    kReadonlyAlias=kBufferIsReadonly,
    kWritableAlias=0
  };
  friend class StringThreadTest;
  union StackBufferOrFields;
  friend union StackBufferOrFields;
  int8_t    fShortLength;
  uint8_t   fFlags;
  union StackBufferOrFields {
    UChar     fStackBuffer [US_STACKBUF_SIZE];
    struct {
      uint16_t  fPadding;
      int32_t   fLength;
      UChar     *fArray;
      int32_t   fCapacity;
    } fFields;
  } fUnion;
};
U_COMMON_API UnicodeString U_EXPORT2
operator+ (const UnicodeString &s1, const UnicodeString &s2);
inline void
UnicodeString::pinIndex(int32_t& start) const
{
  if(start < 0) {
    start = 0;
  } else if(start > length()) {
    start = length();
  }
}
inline void
UnicodeString::pinIndices(int32_t& start,
                          int32_t& _length) const
{
  int32_t len = length();
  if(start < 0) {
    start = 0;
  } else if(start > len) {
    start = len;
  }
  if(_length < 0) {
    _length = 0;
  } else if(_length > (len - start)) {
    _length = (len - start);
  }
}
inline UChar*
UnicodeString::getArrayStart()
{ return (fFlags&kUsingStackBuffer) ? fUnion.fStackBuffer : fUnion.fFields.fArray; }
inline const UChar*
UnicodeString::getArrayStart() const
{ return (fFlags&kUsingStackBuffer) ? fUnion.fStackBuffer : fUnion.fFields.fArray; }
inline int32_t
UnicodeString::length() const
{ return fShortLength>=0 ? fShortLength : fUnion.fFields.fLength; }
inline int32_t
UnicodeString::getCapacity() const
{ return (fFlags&kUsingStackBuffer) ? US_STACKBUF_SIZE : fUnion.fFields.fCapacity; }
inline int32_t
UnicodeString::hashCode() const
{ return doHashCode(); }
inline UBool
UnicodeString::isBogus() const
{ return (UBool)(fFlags & kIsBogus); }
inline UBool
UnicodeString::isWritable() const
{ return (UBool)!(fFlags&(kOpenGetBuffer|kIsBogus)); }
inline UBool
UnicodeString::isBufferWritable() const
{
  return (UBool)(
      !(fFlags&(kOpenGetBuffer|kIsBogus|kBufferIsReadonly)) &&
      (!(fFlags&kRefCounted) || refCount()==1));
}
inline const UChar *
UnicodeString::getBuffer() const {
  if(fFlags&(kIsBogus|kOpenGetBuffer)) {
    return 0;
  } else if(fFlags&kUsingStackBuffer) {
    return fUnion.fStackBuffer;
  } else {
    return fUnion.fFields.fArray;
  }
}
inline int8_t
UnicodeString::doCompare(int32_t start,
              int32_t thisLength,
              const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength) const
{
  if(srcText.isBogus()) {
    return (int8_t)!isBogus();
  } else {
    srcText.pinIndices(srcStart, srcLength);
    return doCompare(start, thisLength, srcText.getArrayStart(), srcStart, srcLength);
  }
}
inline UBool
UnicodeString::operator== (const UnicodeString& text) const
{
  if(isBogus()) {
    return text.isBogus();
  } else {
    int32_t len = length(), textLength = text.length();
    return
      !text.isBogus() &&
      len == textLength &&
      doCompare(0, len, text, 0, textLength) == 0;
  }
}
inline UBool
UnicodeString::operator!= (const UnicodeString& text) const
{ return (! operator==(text)); }
inline UBool
UnicodeString::operator> (const UnicodeString& text) const
{ return doCompare(0, length(), text, 0, text.length()) == 1; }
inline UBool
UnicodeString::operator< (const UnicodeString& text) const
{ return doCompare(0, length(), text, 0, text.length()) == -1; }
inline UBool
UnicodeString::operator>= (const UnicodeString& text) const
{ return doCompare(0, length(), text, 0, text.length()) != -1; }
inline UBool
UnicodeString::operator<= (const UnicodeString& text) const
{ return doCompare(0, length(), text, 0, text.length()) != 1; }
inline int8_t
UnicodeString::compare(const UnicodeString& text) const
{ return doCompare(0, length(), text, 0, text.length()); }
inline int8_t
UnicodeString::compare(int32_t start,
               int32_t _length,
               const UnicodeString& srcText) const
{ return doCompare(start, _length, srcText, 0, srcText.length()); }
inline int8_t
UnicodeString::compare(const UChar *srcChars,
               int32_t srcLength) const
{ return doCompare(0, length(), srcChars, 0, srcLength); }
inline int8_t
UnicodeString::compare(int32_t start,
               int32_t _length,
               const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength) const
{ return doCompare(start, _length, srcText, srcStart, srcLength); }
inline int8_t
UnicodeString::compare(int32_t start,
               int32_t _length,
               const UChar *srcChars) const
{ return doCompare(start, _length, srcChars, 0, _length); }
inline int8_t
UnicodeString::compare(int32_t start,
               int32_t _length,
               const UChar *srcChars,
               int32_t srcStart,
               int32_t srcLength) const
{ return doCompare(start, _length, srcChars, srcStart, srcLength); }
inline int8_t
UnicodeString::compareBetween(int32_t start,
                  int32_t limit,
                  const UnicodeString& srcText,
                  int32_t srcStart,
                  int32_t srcLimit) const
{ return doCompare(start, limit - start,
           srcText, srcStart, srcLimit - srcStart); }
inline int8_t
UnicodeString::doCompareCodePointOrder(int32_t start,
                                       int32_t thisLength,
                                       const UnicodeString& srcText,
                                       int32_t srcStart,
                                       int32_t srcLength) const
{
  if(srcText.isBogus()) {
    return (int8_t)!isBogus();
  } else {
    srcText.pinIndices(srcStart, srcLength);
    return doCompareCodePointOrder(start, thisLength, srcText.getArrayStart(), srcStart, srcLength);
  }
}
inline int8_t
UnicodeString::compareCodePointOrder(const UnicodeString& text) const
{ return doCompareCodePointOrder(0, length(), text, 0, text.length()); }
inline int8_t
UnicodeString::compareCodePointOrder(int32_t start,
                                     int32_t _length,
                                     const UnicodeString& srcText) const
{ return doCompareCodePointOrder(start, _length, srcText, 0, srcText.length()); }
inline int8_t
UnicodeString::compareCodePointOrder(const UChar *srcChars,
                                     int32_t srcLength) const
{ return doCompareCodePointOrder(0, length(), srcChars, 0, srcLength); }
inline int8_t
UnicodeString::compareCodePointOrder(int32_t start,
                                     int32_t _length,
                                     const UnicodeString& srcText,
                                     int32_t srcStart,
                                     int32_t srcLength) const
{ return doCompareCodePointOrder(start, _length, srcText, srcStart, srcLength); }
inline int8_t
UnicodeString::compareCodePointOrder(int32_t start,
                                     int32_t _length,
                                     const UChar *srcChars) const
{ return doCompareCodePointOrder(start, _length, srcChars, 0, _length); }
inline int8_t
UnicodeString::compareCodePointOrder(int32_t start,
                                     int32_t _length,
                                     const UChar *srcChars,
                                     int32_t srcStart,
                                     int32_t srcLength) const
{ return doCompareCodePointOrder(start, _length, srcChars, srcStart, srcLength); }
inline int8_t
UnicodeString::compareCodePointOrderBetween(int32_t start,
                                            int32_t limit,
                                            const UnicodeString& srcText,
                                            int32_t srcStart,
                                            int32_t srcLimit) const
{ return doCompareCodePointOrder(start, limit - start,
           srcText, srcStart, srcLimit - srcStart); }
inline int8_t
UnicodeString::doCaseCompare(int32_t start,
                             int32_t thisLength,
                             const UnicodeString &srcText,
                             int32_t srcStart,
                             int32_t srcLength,
                             uint32_t options) const
{
  if(srcText.isBogus()) {
    return (int8_t)!isBogus();
  } else {
    srcText.pinIndices(srcStart, srcLength);
    return doCaseCompare(start, thisLength, srcText.getArrayStart(), srcStart, srcLength, options);
  }
}
inline int8_t
UnicodeString::caseCompare(const UnicodeString &text, uint32_t options) const {
  return doCaseCompare(0, length(), text, 0, text.length(), options);
}
inline int8_t
UnicodeString::caseCompare(int32_t start,
                           int32_t _length,
                           const UnicodeString &srcText,
                           uint32_t options) const {
  return doCaseCompare(start, _length, srcText, 0, srcText.length(), options);
}
inline int8_t
UnicodeString::caseCompare(const UChar *srcChars,
                           int32_t srcLength,
                           uint32_t options) const {
  return doCaseCompare(0, length(), srcChars, 0, srcLength, options);
}
inline int8_t
UnicodeString::caseCompare(int32_t start,
                           int32_t _length,
                           const UnicodeString &srcText,
                           int32_t srcStart,
                           int32_t srcLength,
                           uint32_t options) const {
  return doCaseCompare(start, _length, srcText, srcStart, srcLength, options);
}
inline int8_t
UnicodeString::caseCompare(int32_t start,
                           int32_t _length,
                           const UChar *srcChars,
                           uint32_t options) const {
  return doCaseCompare(start, _length, srcChars, 0, _length, options);
}
inline int8_t
UnicodeString::caseCompare(int32_t start,
                           int32_t _length,
                           const UChar *srcChars,
                           int32_t srcStart,
                           int32_t srcLength,
                           uint32_t options) const {
  return doCaseCompare(start, _length, srcChars, srcStart, srcLength, options);
}
inline int8_t
UnicodeString::caseCompareBetween(int32_t start,
                                  int32_t limit,
                                  const UnicodeString &srcText,
                                  int32_t srcStart,
                                  int32_t srcLimit,
                                  uint32_t options) const {
  return doCaseCompare(start, limit - start, srcText, srcStart, srcLimit - srcStart, options);
}
inline int32_t
UnicodeString::indexOf(const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength,
               int32_t start,
               int32_t _length) const
{
  if(!srcText.isBogus()) {
    srcText.pinIndices(srcStart, srcLength);
    if(srcLength > 0) {
      return indexOf(srcText.getArrayStart(), srcStart, srcLength, start, _length);
    }
  }
  return -1;
}
inline int32_t
UnicodeString::indexOf(const UnicodeString& text) const
{ return indexOf(text, 0, text.length(), 0, length()); }
inline int32_t
UnicodeString::indexOf(const UnicodeString& text,
               int32_t start) const {
  pinIndex(start);
  return indexOf(text, 0, text.length(), start, length() - start);
}
inline int32_t
UnicodeString::indexOf(const UnicodeString& text,
               int32_t start,
               int32_t _length) const
{ return indexOf(text, 0, text.length(), start, _length); }
inline int32_t
UnicodeString::indexOf(const UChar *srcChars,
               int32_t srcLength,
               int32_t start) const {
  pinIndex(start);
  return indexOf(srcChars, 0, srcLength, start, length() - start);
}
inline int32_t
UnicodeString::indexOf(const UChar *srcChars,
               int32_t srcLength,
               int32_t start,
               int32_t _length) const
{ return indexOf(srcChars, 0, srcLength, start, _length); }
inline int32_t
UnicodeString::indexOf(UChar c,
               int32_t start,
               int32_t _length) const
{ return doIndexOf(c, start, _length); }
inline int32_t
UnicodeString::indexOf(UChar32 c,
               int32_t start,
               int32_t _length) const
{ return doIndexOf(c, start, _length); }
inline int32_t
UnicodeString::indexOf(UChar c) const
{ return doIndexOf(c, 0, length()); }
inline int32_t
UnicodeString::indexOf(UChar32 c) const
{ return indexOf(c, 0, length()); }
inline int32_t
UnicodeString::indexOf(UChar c,
               int32_t start) const {
  pinIndex(start);
  return doIndexOf(c, start, length() - start);
}
inline int32_t
UnicodeString::indexOf(UChar32 c,
               int32_t start) const {
  pinIndex(start);
  return indexOf(c, start, length() - start);
}
inline int32_t
UnicodeString::lastIndexOf(const UChar *srcChars,
               int32_t srcLength,
               int32_t start,
               int32_t _length) const
{ return lastIndexOf(srcChars, 0, srcLength, start, _length); }
inline int32_t
UnicodeString::lastIndexOf(const UChar *srcChars,
               int32_t srcLength,
               int32_t start) const {
  pinIndex(start);
  return lastIndexOf(srcChars, 0, srcLength, start, length() - start);
}
inline int32_t
UnicodeString::lastIndexOf(const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength,
               int32_t start,
               int32_t _length) const
{
  if(!srcText.isBogus()) {
    srcText.pinIndices(srcStart, srcLength);
    if(srcLength > 0) {
      return lastIndexOf(srcText.getArrayStart(), srcStart, srcLength, start, _length);
    }
  }
  return -1;
}
inline int32_t
UnicodeString::lastIndexOf(const UnicodeString& text,
               int32_t start,
               int32_t _length) const
{ return lastIndexOf(text, 0, text.length(), start, _length); }
inline int32_t
UnicodeString::lastIndexOf(const UnicodeString& text,
               int32_t start) const {
  pinIndex(start);
  return lastIndexOf(text, 0, text.length(), start, length() - start);
}
inline int32_t
UnicodeString::lastIndexOf(const UnicodeString& text) const
{ return lastIndexOf(text, 0, text.length(), 0, length()); }
inline int32_t
UnicodeString::lastIndexOf(UChar c,
               int32_t start,
               int32_t _length) const
{ return doLastIndexOf(c, start, _length); }
inline int32_t
UnicodeString::lastIndexOf(UChar32 c,
               int32_t start,
               int32_t _length) const {
  return doLastIndexOf(c, start, _length);
}
inline int32_t
UnicodeString::lastIndexOf(UChar c) const
{ return doLastIndexOf(c, 0, length()); }
inline int32_t
UnicodeString::lastIndexOf(UChar32 c) const {
  return lastIndexOf(c, 0, length());
}
inline int32_t
UnicodeString::lastIndexOf(UChar c,
               int32_t start) const {
  pinIndex(start);
  return doLastIndexOf(c, start, length() - start);
}
inline int32_t
UnicodeString::lastIndexOf(UChar32 c,
               int32_t start) const {
  pinIndex(start);
  return lastIndexOf(c, start, length() - start);
}
inline UBool
UnicodeString::startsWith(const UnicodeString& text) const
{ return compare(0, text.length(), text, 0, text.length()) == 0; }
inline UBool
UnicodeString::startsWith(const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength) const
{ return doCompare(0, srcLength, srcText, srcStart, srcLength) == 0; }
inline UBool
UnicodeString::startsWith(const UChar *srcChars,
              int32_t srcLength) const
{ return doCompare(0, srcLength, srcChars, 0, srcLength) == 0; }
inline UBool
UnicodeString::startsWith(const UChar *srcChars,
              int32_t srcStart,
              int32_t srcLength) const
{ return doCompare(0, srcLength, srcChars, srcStart, srcLength) == 0;}
inline UBool
UnicodeString::endsWith(const UnicodeString& text) const
{ return doCompare(length() - text.length(), text.length(),
           text, 0, text.length()) == 0; }
inline UBool
UnicodeString::endsWith(const UnicodeString& srcText,
            int32_t srcStart,
            int32_t srcLength) const {
  srcText.pinIndices(srcStart, srcLength);
  return doCompare(length() - srcLength, srcLength,
                   srcText, srcStart, srcLength) == 0;
}
inline UBool
UnicodeString::endsWith(const UChar *srcChars,
            int32_t srcLength) const {
  if(srcLength < 0) {
    srcLength = u_strlen(srcChars);
  }
  return doCompare(length() - srcLength, srcLength,
                   srcChars, 0, srcLength) == 0;
}
inline UBool
UnicodeString::endsWith(const UChar *srcChars,
            int32_t srcStart,
            int32_t srcLength) const {
  if(srcLength < 0) {
    srcLength = u_strlen(srcChars + srcStart);
  }
  return doCompare(length() - srcLength, srcLength,
                   srcChars, srcStart, srcLength) == 0;
}
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               const UnicodeString& srcText)
{ return doReplace(start, _length, srcText, 0, srcText.length()); }
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               const UnicodeString& srcText,
               int32_t srcStart,
               int32_t srcLength)
{ return doReplace(start, _length, srcText, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               const UChar *srcChars,
               int32_t srcLength)
{ return doReplace(start, _length, srcChars, 0, srcLength); }
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               const UChar *srcChars,
               int32_t srcStart,
               int32_t srcLength)
{ return doReplace(start, _length, srcChars, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               UChar srcChar)
{ return doReplace(start, _length, &srcChar, 0, 1); }
inline UnicodeString&
UnicodeString::replace(int32_t start,
               int32_t _length,
               UChar32 srcChar) {
  UChar buffer[U16_MAX_LENGTH];
  int32_t count = 0;
  UBool isError = FALSE;
  U16_APPEND(buffer, count, U16_MAX_LENGTH, srcChar, isError);
  return doReplace(start, _length, buffer, 0, count);
}
inline UnicodeString&
UnicodeString::replaceBetween(int32_t start,
                  int32_t limit,
                  const UnicodeString& srcText)
{ return doReplace(start, limit - start, srcText, 0, srcText.length()); }
inline UnicodeString&
UnicodeString::replaceBetween(int32_t start,
                  int32_t limit,
                  const UnicodeString& srcText,
                  int32_t srcStart,
                  int32_t srcLimit)
{ return doReplace(start, limit - start, srcText, srcStart, srcLimit - srcStart); }
inline UnicodeString&
UnicodeString::findAndReplace(const UnicodeString& oldText,
                  const UnicodeString& newText)
{ return findAndReplace(0, length(), oldText, 0, oldText.length(),
            newText, 0, newText.length()); }
inline UnicodeString&
UnicodeString::findAndReplace(int32_t start,
                  int32_t _length,
                  const UnicodeString& oldText,
                  const UnicodeString& newText)
{ return findAndReplace(start, _length, oldText, 0, oldText.length(),
            newText, 0, newText.length()); }
inline void
UnicodeString::doExtract(int32_t start,
             int32_t _length,
             UnicodeString& target) const
{ target.replace(0, target.length(), *this, start, _length); }
inline void
UnicodeString::extract(int32_t start,
               int32_t _length,
               UChar *target,
               int32_t targetStart) const
{ doExtract(start, _length, target, targetStart); }
inline void
UnicodeString::extract(int32_t start,
               int32_t _length,
               UnicodeString& target) const
{ doExtract(start, _length, target); }
#if !UCONFIG_NO_CONVERSION
inline int32_t
UnicodeString::extract(int32_t start,
               int32_t _length,
               char *dst,
               const char *codepage) const
{
#if defined(__GNUC__)
  return extract(start, _length, dst, dst!=0 ? ((dst >= (char*)((size_t)-1) - UINT32_MAX) ? (((char*)UINT32_MAX) - dst) : UINT32_MAX) : 0, codepage);
#else
  return extract(start, _length, dst, dst!=0 ? 0xffffffff : 0, codepage);
#endif
}
#endif
inline void
UnicodeString::extractBetween(int32_t start,
                  int32_t limit,
                  UChar *dst,
                  int32_t dstStart) const {
  pinIndex(start);
  pinIndex(limit);
  doExtract(start, limit - start, dst, dstStart);
}
inline UnicodeString
UnicodeString::tempSubStringBetween(int32_t start, int32_t limit) const {
    return tempSubString(start, limit - start);
}
inline UChar
UnicodeString::doCharAt(int32_t offset) const
{
  if((uint32_t)offset < (uint32_t)length()) {
    return getArrayStart()[offset];
  } else {
    return kInvalidUChar;
  }
}
inline UChar
UnicodeString::charAt(int32_t offset) const
{ return doCharAt(offset); }
inline UChar
UnicodeString::operator[] (int32_t offset) const
{ return doCharAt(offset); }
inline UChar32
UnicodeString::char32At(int32_t offset) const
{
  int32_t len = length();
  if((uint32_t)offset < (uint32_t)len) {
    const UChar *array = getArrayStart();
    UChar32 c;
    U16_GET(array, 0, offset, len, c);
    return c;
  } else {
    return kInvalidUChar;
  }
}
inline int32_t
UnicodeString::getChar32Start(int32_t offset) const {
  if((uint32_t)offset < (uint32_t)length()) {
    const UChar *array = getArrayStart();
    U16_SET_CP_START(array, 0, offset);
    return offset;
  } else {
    return 0;
  }
}
inline int32_t
UnicodeString::getChar32Limit(int32_t offset) const {
  int32_t len = length();
  if((uint32_t)offset < (uint32_t)len) {
    const UChar *array = getArrayStart();
    U16_SET_CP_LIMIT(array, 0, offset, len);
    return offset;
  } else {
    return len;
  }
}
inline UBool
UnicodeString::isEmpty() const {
  return fShortLength == 0;
}
inline void
UnicodeString::setLength(int32_t len) {
  if(len <= 127) {
    fShortLength = (int8_t)len;
  } else {
    fShortLength = (int8_t)-1;
    fUnion.fFields.fLength = len;
  }
}
inline void
UnicodeString::setToEmpty() {
  fShortLength = 0;
  fFlags = kShortString;
}
inline void
UnicodeString::setArray(UChar *array, int32_t len, int32_t capacity) {
  setLength(len);
  fUnion.fFields.fArray = array;
  fUnion.fFields.fCapacity = capacity;
}
inline const UChar *
UnicodeString::getTerminatedBuffer() {
  if(!isWritable()) {
    return 0;
  } else {
    UChar *array = getArrayStart();
    int32_t len = length();
    if(len < getCapacity() && ((fFlags&kRefCounted) == 0 || refCount() == 1)) {
      if(!(fFlags&kBufferIsReadonly)) {
        array[len] = 0;
      }
      return array;
    } else if(cloneArrayIfNeeded(len+1)) {
      array = getArrayStart();
      array[len] = 0;
      return array;
    } else {
      return 0;
    }
  }
}
inline UnicodeString&
UnicodeString::operator= (UChar ch)
{ return doReplace(0, length(), &ch, 0, 1); }
inline UnicodeString&
UnicodeString::operator= (UChar32 ch)
{ return replace(0, length(), ch); }
inline UnicodeString&
UnicodeString::setTo(const UnicodeString& srcText,
             int32_t srcStart,
             int32_t srcLength)
{
  unBogus();
  return doReplace(0, length(), srcText, srcStart, srcLength);
}
inline UnicodeString&
UnicodeString::setTo(const UnicodeString& srcText,
             int32_t srcStart)
{
  unBogus();
  srcText.pinIndex(srcStart);
  return doReplace(0, length(), srcText, srcStart, srcText.length() - srcStart);
}
inline UnicodeString&
UnicodeString::setTo(const UnicodeString& srcText)
{
  unBogus();
  return doReplace(0, length(), srcText, 0, srcText.length());
}
inline UnicodeString&
UnicodeString::setTo(const UChar *srcChars,
             int32_t srcLength)
{
  unBogus();
  return doReplace(0, length(), srcChars, 0, srcLength);
}
inline UnicodeString&
UnicodeString::setTo(UChar srcChar)
{
  unBogus();
  return doReplace(0, length(), &srcChar, 0, 1);
}
inline UnicodeString&
UnicodeString::setTo(UChar32 srcChar)
{
  unBogus();
  return replace(0, length(), srcChar);
}
inline UnicodeString&
UnicodeString::append(const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength)
{ return doReplace(length(), 0, srcText, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::append(const UnicodeString& srcText)
{ return doReplace(length(), 0, srcText, 0, srcText.length()); }
inline UnicodeString&
UnicodeString::append(const UChar *srcChars,
              int32_t srcStart,
              int32_t srcLength)
{ return doReplace(length(), 0, srcChars, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::append(const UChar *srcChars,
              int32_t srcLength)
{ return doReplace(length(), 0, srcChars, 0, srcLength); }
inline UnicodeString&
UnicodeString::append(UChar srcChar)
{ return doReplace(length(), 0, &srcChar, 0, 1); }
inline UnicodeString&
UnicodeString::append(UChar32 srcChar) {
  UChar buffer[U16_MAX_LENGTH];
  int32_t _length = 0;
  UBool isError = FALSE;
  U16_APPEND(buffer, _length, U16_MAX_LENGTH, srcChar, isError);
  return doReplace(length(), 0, buffer, 0, _length);
}
inline UnicodeString&
UnicodeString::operator+= (UChar ch)
{ return doReplace(length(), 0, &ch, 0, 1); }
inline UnicodeString&
UnicodeString::operator+= (UChar32 ch) {
  return append(ch);
}
inline UnicodeString&
UnicodeString::operator+= (const UnicodeString& srcText)
{ return doReplace(length(), 0, srcText, 0, srcText.length()); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              const UnicodeString& srcText,
              int32_t srcStart,
              int32_t srcLength)
{ return doReplace(start, 0, srcText, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              const UnicodeString& srcText)
{ return doReplace(start, 0, srcText, 0, srcText.length()); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              const UChar *srcChars,
              int32_t srcStart,
              int32_t srcLength)
{ return doReplace(start, 0, srcChars, srcStart, srcLength); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              const UChar *srcChars,
              int32_t srcLength)
{ return doReplace(start, 0, srcChars, 0, srcLength); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              UChar srcChar)
{ return doReplace(start, 0, &srcChar, 0, 1); }
inline UnicodeString&
UnicodeString::insert(int32_t start,
              UChar32 srcChar)
{ return replace(start, 0, srcChar); }
inline UnicodeString&
UnicodeString::remove()
{
  if(fFlags & (kIsBogus|kBufferIsReadonly)) {
    setToEmpty();
  } else {
    fShortLength = 0;
  }
  return *this;
}
inline UnicodeString&
UnicodeString::remove(int32_t start,
             int32_t _length)
{
    if(start <= 0 && _length == INT32_MAX) {
        return remove();
    }
    return doReplace(start, _length, NULL, 0, 0);
}
inline UnicodeString&
UnicodeString::removeBetween(int32_t start,
                int32_t limit)
{ return doReplace(start, limit - start, NULL, 0, 0); }
inline UnicodeString &
UnicodeString::retainBetween(int32_t start, int32_t limit) {
  truncate(limit);
  return doReplace(0, start, NULL, 0, 0);
}
inline UBool
UnicodeString::truncate(int32_t targetLength)
{
  if(isBogus() && targetLength == 0) {
    unBogus();
    return FALSE;
  } else if((uint32_t)targetLength < (uint32_t)length()) {
    setLength(targetLength);
    if(fFlags&kBufferIsReadonly) {
      fUnion.fFields.fCapacity = targetLength;
    }
    return TRUE;
  } else {
    return FALSE;
  }
}
inline UnicodeString&
UnicodeString::reverse()
{ return doReverse(0, length()); }
inline UnicodeString&
UnicodeString::reverse(int32_t start,
               int32_t _length)
{ return doReverse(start, _length); }
U_NAMESPACE_END
#endif
