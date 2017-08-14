#ifndef TRANSLIT_H
#define TRANSLIT_H
#include "unicode/utypes.h"
#if !UCONFIG_NO_TRANSLITERATION
#include "unicode/uobject.h"
#include "unicode/unistr.h"
#include "unicode/parseerr.h"
#include "unicode/utrans.h"
#include "unicode/strenum.h"
U_NAMESPACE_BEGIN
class UnicodeFilter;
class UnicodeSet;
class CompoundTransliterator;
class TransliteratorParser;
class NormalizationTransliterator;
class TransliteratorIDParser;
class U_I18N_API Transliterator : public UObject {
private:
    UnicodeString ID;
    UnicodeFilter* filter;
    int32_t maximumContextLength;
 public:
    union Token {
        int32_t integer;
        void*   pointer;
    };
    inline static Token integerToken(int32_t);
    inline static Token pointerToken(void*);
    typedef Transliterator* (U_EXPORT2 *Factory)(const UnicodeString& ID, Token context);
protected:
    Transliterator(const UnicodeString& ID, UnicodeFilter* adoptedFilter);
    Transliterator(const Transliterator&);
    Transliterator& operator=(const Transliterator&);
    static Transliterator* createBasicInstance(const UnicodeString& id,
                                               const UnicodeString* canon);
    friend class TransliteratorParser;
    friend class TransliteratorIDParser;
    friend class TransliteratorAlias;
public:
    virtual ~Transliterator();
    virtual Transliterator* clone() const;
    virtual int32_t transliterate(Replaceable& text,
                                  int32_t start, int32_t limit) const;
    virtual void transliterate(Replaceable& text) const;
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               const UnicodeString& insertion,
                               UErrorCode& status) const;
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               UChar32 insertion,
                               UErrorCode& status) const;
    virtual void transliterate(Replaceable& text, UTransPosition& index,
                               UErrorCode& status) const;
    virtual void finishTransliteration(Replaceable& text,
                                       UTransPosition& index) const;
private:
    void _transliterate(Replaceable& text,
                        UTransPosition& index,
                        const UnicodeString* insertion,
                        UErrorCode &status) const;
protected:
    virtual void handleTransliterate(Replaceable& text,
                                     UTransPosition& pos,
                                     UBool incremental) const = 0;
public:
    virtual void filteredTransliterate(Replaceable& text,
                                       UTransPosition& index,
                                       UBool incremental) const;
private:
    virtual void filteredTransliterate(Replaceable& text,
                                       UTransPosition& index,
                                       UBool incremental,
                                       UBool rollback) const;
public:
    int32_t getMaximumContextLength(void) const;
protected:
    void setMaximumContextLength(int32_t maxContextLength);
public:
    virtual const UnicodeString& getID(void) const;
    static UnicodeString& U_EXPORT2 getDisplayName(const UnicodeString& ID,
                                         UnicodeString& result);
    static UnicodeString& U_EXPORT2 getDisplayName(const UnicodeString& ID,
                                         const Locale& inLocale,
                                         UnicodeString& result);
    const UnicodeFilter* getFilter(void) const;
    UnicodeFilter* orphanFilter(void);
    void adoptFilter(UnicodeFilter* adoptedFilter);
    Transliterator* createInverse(UErrorCode& status) const;
    static Transliterator* U_EXPORT2 createInstance(const UnicodeString& ID,
                                          UTransDirection dir,
                                          UParseError& parseError,
                                          UErrorCode& status);
    static Transliterator* U_EXPORT2 createInstance(const UnicodeString& ID,
                                          UTransDirection dir,
                                          UErrorCode& status);
    static Transliterator* U_EXPORT2 createFromRules(const UnicodeString& ID,
                                           const UnicodeString& rules,
                                           UTransDirection dir,
                                           UParseError& parseError,
                                           UErrorCode& status);
    virtual UnicodeString& toRules(UnicodeString& result,
                                   UBool escapeUnprintable) const;
    int32_t countElements() const;
    const Transliterator& getElement(int32_t index, UErrorCode& ec) const;
    UnicodeSet& getSourceSet(UnicodeSet& result) const;
    virtual void handleGetSourceSet(UnicodeSet& result) const;
    virtual UnicodeSet& getTargetSet(UnicodeSet& result) const;
public:
    static void U_EXPORT2 registerFactory(const UnicodeString& id,
                                Factory factory,
                                Token context);
    static void U_EXPORT2 registerInstance(Transliterator* adoptedObj);
     static void U_EXPORT2 registerAlias(const UnicodeString& aliasID,
                                         const UnicodeString& realID);
protected:
    static void _registerFactory(const UnicodeString& id,
                                 Factory factory,
                                 Token context);
    static void _registerInstance(Transliterator* adoptedObj);
    static void _registerAlias(const UnicodeString& aliasID, const UnicodeString& realID);
    static void _registerSpecialInverse(const UnicodeString& target,
                                        const UnicodeString& inverseTarget,
                                        UBool bidirectional);
public:
    static void U_EXPORT2 unregister(const UnicodeString& ID);
public:
    static StringEnumeration* U_EXPORT2 getAvailableIDs(UErrorCode& ec);
    static int32_t U_EXPORT2 countAvailableSources(void);
    static UnicodeString& U_EXPORT2 getAvailableSource(int32_t index,
                                             UnicodeString& result);
    static int32_t U_EXPORT2 countAvailableTargets(const UnicodeString& source);
    static UnicodeString& U_EXPORT2 getAvailableTarget(int32_t index,
                                             const UnicodeString& source,
                                             UnicodeString& result);
    static int32_t U_EXPORT2 countAvailableVariants(const UnicodeString& source,
                                          const UnicodeString& target);
    static UnicodeString& U_EXPORT2 getAvailableVariant(int32_t index,
                                              const UnicodeString& source,
                                              const UnicodeString& target,
                                              UnicodeString& result);
protected:
    static int32_t _countAvailableSources(void);
    static UnicodeString& _getAvailableSource(int32_t index,
                                              UnicodeString& result);
    static int32_t _countAvailableTargets(const UnicodeString& source);
    static UnicodeString& _getAvailableTarget(int32_t index,
                                              const UnicodeString& source,
                                              UnicodeString& result);
    static int32_t _countAvailableVariants(const UnicodeString& source,
                                           const UnicodeString& target);
    static UnicodeString& _getAvailableVariant(int32_t index,
                                               const UnicodeString& source,
                                               const UnicodeString& target,
                                               UnicodeString& result);
protected:
    void setID(const UnicodeString& id);
public:
    static UClassID U_EXPORT2 getStaticClassID(void);
    virtual UClassID getDynamicClassID(void) const = 0;
private:
    static UBool initializeRegistry(UErrorCode &status);
public:
    static int32_t U_EXPORT2 countAvailableIDs(void);
    static const UnicodeString& U_EXPORT2 getAvailableID(int32_t index);
};
inline int32_t Transliterator::getMaximumContextLength(void) const {
    return maximumContextLength;
}
inline void Transliterator::setID(const UnicodeString& id) {
    ID = id;
    ID.append((UChar)0);
    ID.truncate(ID.length()-1);
}
inline Transliterator::Token Transliterator::integerToken(int32_t i) {
    Token t;
    t.integer = i;
    return t;
}
inline Transliterator::Token Transliterator::pointerToken(void* p) {
    Token t;
    t.pointer = p;
    return t;
}
U_NAMESPACE_END
#endif
#endif
