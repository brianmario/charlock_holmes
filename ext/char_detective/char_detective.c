#include "ruby.h"
#include "unicode/ucsdet.h"

/*
 * call-seq: detection_hash = CharDetective.detect "some string"
 *
 * Attempt to detect the encoding of this string
 *
 * Returns: a Hash with :encoding, :language and :confidence
 */
static VALUE mCharDetective_detect(VALUE self, VALUE str) {
  char *str;
  int32_t len;
  VALUE ret = Qnil;
  UErrorCode status = U_ZERO_ERROR;
  UCharsetDetector *csd;
  const UCharsetMatch *match;
  const char *encodingName;
  const char *encodingLanguage;
  int32_t confidence;

  Check_Type(str, T_STRING);
  str = RSTRING_PTR(str);
  len = (int32_t)RSTRING_LEN(str);

  csd = ucsdet_open(&status);

  ucsdet_setText(csd, str, len, &status);

  match = ucsdet_detect(csd, &status);

  if (match) {
    encodingName = ucsdet_getName(match, &status);
    encodingLanguage = ucsdet_getLanguage(match, &status);
    confidence = ucsdet_getConfidence(match, &status);

    ret = rb_hash_new();
    rb_hash_aset(ret, ID2SYM(rb_intern("encoding")), rb_str_new2(encodingName));
    if (strlen(encodingLanguage)) {
      rb_hash_aset(ret, ID2SYM(rb_intern("language")), rb_str_new2(encodingLanguage));
    } else {
      rb_hash_aset(ret, ID2SYM(rb_intern("language")), Qnil);
    }
    rb_hash_aset(ret, ID2SYM(rb_intern("confidence")), INT2NUM(confidence));
  }

  ucsdet_close(csd);

  return ret;
}

void Init_char_detective() {
  VALUE mCharDetective = rb_define_module("CharDetective");

  rb_define_method(mCharDetective, "detect", mCharDetective_detect, 1);
}