#ifndef __BYTESTREAM_H__
#define __BYTESTREAM_H__
#include "unicode/utypes.h"
#include "unicode/uobject.h"
#include "unicode/std_string.h"
U_NAMESPACE_BEGIN
class U_COMMON_API ByteSink : public UMemory {
public:
  ByteSink() { }
  virtual ~ByteSink() { }
  virtual void Append(const char* bytes, int32_t n) = 0;
  virtual char* GetAppendBuffer(int32_t min_capacity,
                                int32_t desired_capacity_hint,
                                char* scratch, int32_t scratch_capacity,
                                int32_t* result_capacity);
  virtual void Flush();
private:
  ByteSink(const ByteSink &);
  ByteSink &operator=(const ByteSink &);
};
class U_COMMON_API CheckedArrayByteSink : public ByteSink {
public:
  CheckedArrayByteSink(char* outbuf, int32_t capacity);
  virtual CheckedArrayByteSink& Reset();
  virtual void Append(const char* bytes, int32_t n);
  virtual char* GetAppendBuffer(int32_t min_capacity,
                                int32_t desired_capacity_hint,
                                char* scratch, int32_t scratch_capacity,
                                int32_t* result_capacity);
  int32_t NumberOfBytesWritten() const { return size_; }
  UBool Overflowed() const { return overflowed_; }
  int32_t NumberOfBytesAppended() const { return appended_; }
private:
  char* outbuf_;
  const int32_t capacity_;
  int32_t size_;
  int32_t appended_;
  UBool overflowed_;
  CheckedArrayByteSink();
  CheckedArrayByteSink(const CheckedArrayByteSink &);
  CheckedArrayByteSink &operator=(const CheckedArrayByteSink &);
};
#if U_HAVE_STD_STRING
template<typename StringClass>
class StringByteSink : public ByteSink {
 public:
  StringByteSink(StringClass* dest) : dest_(dest) { }
  virtual void Append(const char* data, int32_t n) { dest_->append(data, n); }
 private:
  StringClass* dest_;
  StringByteSink();
  StringByteSink(const StringByteSink &);
  StringByteSink &operator=(const StringByteSink &);
};
#endif
U_NAMESPACE_END
#endif
