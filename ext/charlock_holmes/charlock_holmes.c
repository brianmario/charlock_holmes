#include "ruby.h"
#include "unicode/ucsdet.h"

/*
 * call-seq: detection_hash = CharlockHolmes.detect "some string"
 *
 * Attempt to detect the encoding of this string
 *
 * Returns: a Hash with :encoding, :language and :confidence
 */
static VALUE mCharlockHolmes_detect(VALUE self, VALUE str) {
  char *buf;
  int32_t len;
  VALUE ret = Qnil;
  UErrorCode status = U_ZERO_ERROR;
  UCharsetDetector *csd;
  const UCharsetMatch *match;
  const char *encodingName;
  const char *encodingLanguage;
  int32_t confidence;

  Check_Type(str, T_STRING);
  buf = RSTRING_PTR(str);
  len = (int32_t)RSTRING_LEN(str);

  csd = ucsdet_open(&status);

  ucsdet_setText(csd, buf, len, &status);

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

void Init_charlock_holmes() {
  VALUE mCharlockHolmes = rb_define_module("CharlockHolmes");

  rb_define_method(mCharlockHolmes, "detect", mCharlockHolmes_detect, 1);
}