#ifndef __UOBJECT_H__
#define __UOBJECT_H__
#include "unicode/utypes.h"
U_NAMESPACE_BEGIN
#ifndef U_OVERRIDE_CXX_ALLOCATION
#define U_OVERRIDE_CXX_ALLOCATION 1
#endif
#ifndef U_HAVE_PLACEMENT_NEW
#define U_HAVE_PLACEMENT_NEW 1
#endif
#ifndef U_HAVE_DEBUG_LOCATION_NEW
#define U_HAVE_DEBUG_LOCATION_NEW 0
#endif
#ifndef U_NO_THROW
#define U_NO_THROW throw()
#endif
class U_COMMON_API UMemory {
public:
#ifdef SHAPER_MEMORY_DEBUG
    static void * NewArray(int size, int count);
    static void * GrowArray(void * array, int newSize );
    static void   FreeArray(void * array );
#endif
#if U_OVERRIDE_CXX_ALLOCATION
    static void * U_EXPORT2 operator new(size_t size) U_NO_THROW;
    static void * U_EXPORT2 operator new[](size_t size) U_NO_THROW;
    static void U_EXPORT2 operator delete(void *p) U_NO_THROW;
    static void U_EXPORT2 operator delete[](void *p) U_NO_THROW;
#if U_HAVE_PLACEMENT_NEW
    static inline void * U_EXPORT2 operator new(size_t, void *ptr) U_NO_THROW { return ptr; }
    static inline void U_EXPORT2 operator delete(void *, void *) U_NO_THROW {}
#endif
#if U_HAVE_DEBUG_LOCATION_NEW
    static void * U_EXPORT2 operator new(size_t size, const char* file, int line) U_NO_THROW;
    static void U_EXPORT2 operator delete(void* p, const char* file, int line) U_NO_THROW;
#endif
#endif
};
class U_COMMON_API UObject : public UMemory {
public:
    virtual ~UObject();
    virtual UClassID getDynamicClassID() const = 0;
protected:
#if 0
    virtual inline UBool operator==(const UObject &other) const { return this==&other; }
    inline UBool operator!=(const UObject &other) const { return !operator==(other); }
#endif
};
#define UOBJECT_DEFINE_RTTI_IMPLEMENTATION(myClass) \
    UClassID U_EXPORT2 myClass::getStaticClassID() { \
        static char classID = 0; \
        return (UClassID)&classID; \
    } \
    UClassID myClass::getDynamicClassID() const \
    { return myClass::getStaticClassID(); }
#define UOBJECT_DEFINE_ABSTRACT_RTTI_IMPLEMENTATION(myClass) \
    UClassID U_EXPORT2 myClass::getStaticClassID() { \
        static char classID = 0; \
        return (UClassID)&classID; \
    }
#define UOBJECT_DEFINE_NO_RTTI_IMPLEMENTATION(myClass) \
    UClassID myClass::getDynamicClassID() const { return NULL; }
U_NAMESPACE_END
#endif
