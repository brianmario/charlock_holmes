#ifndef __STRINGPIECE_H__
#define __STRINGPIECE_H__
#include "unicode/utypes.h"
#include "unicode/uobject.h"
#include "unicode/std_string.h"
U_NAMESPACE_BEGIN
class U_COMMON_API StringPiece : public UMemory {
 private:
  const char*   ptr_;
  int32_t       length_;
 public:
  StringPiece() : ptr_(NULL), length_(0) { }
  StringPiece(const char* str);
#if U_HAVE_STD_STRING
  StringPiece(const U_STD_NSQ string& str)
    : ptr_(str.data()), length_(static_cast<int32_t>(str.size())) { }
#endif
  StringPiece(const char* offset, int32_t len) : ptr_(offset), length_(len) { }
  StringPiece(const StringPiece& x, int32_t pos);
  StringPiece(const StringPiece& x, int32_t pos, int32_t len);
  const char* data() const { return ptr_; }
  int32_t size() const { return length_; }
  int32_t length() const { return length_; }
  UBool empty() const { return length_ == 0; }
  void clear() { ptr_ = NULL; length_ = 0; }
  void set(const char* data, int32_t len) { ptr_ = data; length_ = len; }
  void set(const char* str);
  void remove_prefix(int32_t n) {
    if (n >= 0) {
      if (n > length_) {
        n = length_;
      }
      ptr_ += n;
      length_ -= n;
    }
  }
  void remove_suffix(int32_t n) {
    if (n >= 0) {
      if (n <= length_) {
        length_ -= n;
      } else {
        length_ = 0;
      }
    }
  }
  static const int32_t npos = 0x7fffffff;
  StringPiece substr(int32_t pos, int32_t len = npos) const {
    return StringPiece(*this, pos, len);
  }
};
U_EXPORT UBool U_EXPORT2
operator==(const StringPiece& x, const StringPiece& y);
inline UBool operator!=(const StringPiece& x, const StringPiece& y) {
  return !(x == y);
}
U_NAMESPACE_END
#endif
