#ifndef __LOCALPOINTER_H__
#define __LOCALPOINTER_H__
#include "unicode/utypes.h"
#if U_SHOW_CPLUSPLUS_API
U_NAMESPACE_BEGIN
template<typename T>
class LocalPointerBase {
public:
    explicit LocalPointerBase(T *p=NULL) : ptr(p) {}
    ~LocalPointerBase() {  }
    UBool isNull() const { return ptr==NULL; }
    UBool isValid() const { return ptr!=NULL; }
    bool operator==(const T *other) const { return ptr==other; }
    bool operator!=(const T *other) const { return ptr!=other; }
    T *getAlias() const { return ptr; }
    T &operator*() const { return *ptr; }
    T *operator->() const { return ptr; }
    T *orphan() {
        T *p=ptr;
        ptr=NULL;
        return p;
    }
    void adoptInstead(T *p) {
        ptr=p;
    }
protected:
    T *ptr;
private:
    bool operator==(const LocalPointerBase &other);
    bool operator!=(const LocalPointerBase &other);
    LocalPointerBase(const LocalPointerBase &other);
    void operator=(const LocalPointerBase &other);
    static void * U_EXPORT2 operator new(size_t size);
    static void * U_EXPORT2 operator new[](size_t size);
#if U_HAVE_PLACEMENT_NEW
    static void * U_EXPORT2 operator new(size_t, void *ptr);
#endif
};
template<typename T>
class LocalPointer : public LocalPointerBase<T> {
public:
    explicit LocalPointer(T *p=NULL) : LocalPointerBase<T>(p) {}
    ~LocalPointer() {
        delete LocalPointerBase<T>::ptr;
    }
    void adoptInstead(T *p) {
        delete LocalPointerBase<T>::ptr;
        LocalPointerBase<T>::ptr=p;
    }
};
template<typename T>
class LocalArray : public LocalPointerBase<T> {
public:
    explicit LocalArray(T *p=NULL) : LocalPointerBase<T>(p) {}
    ~LocalArray() {
        delete[] LocalPointerBase<T>::ptr;
    }
    void adoptInstead(T *p) {
        delete[] LocalPointerBase<T>::ptr;
        LocalPointerBase<T>::ptr=p;
    }
    T &operator[](ptrdiff_t i) const { return LocalPointerBase<T>::ptr[i]; }
};
#define U_DEFINE_LOCAL_OPEN_POINTER(LocalPointerClassName, Type, closeFunction) \
    class LocalPointerClassName : public LocalPointerBase<Type> { \
    public: \
        explicit LocalPointerClassName(Type *p=NULL) : LocalPointerBase<Type>(p) {} \
        ~LocalPointerClassName() { closeFunction(ptr); } \
        void adoptInstead(Type *p) { \
            closeFunction(ptr); \
            ptr=p; \
        } \
    }
U_NAMESPACE_END
#endif
#endif
