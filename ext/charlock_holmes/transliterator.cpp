#include "common.h"
#undef UChar

#include <unicode/translit.h>

extern "C" {

extern VALUE rb_mCharlockHolmes;
static VALUE rb_cTransliterator;

static VALUE rb_transliterator_transliterate(VALUE self, VALUE rb_txt, VALUE rb_id) {
  UErrorCode status = U_ZERO_ERROR;
  UParseError p_error;
  Transliterator *trans;
  const char *txt;
  size_t txt_len;
  const char *id;
  size_t id_len;
  UnicodeString *u_txt;
  std::string result;
  VALUE rb_out;

  Check_Type(rb_txt, T_STRING);
  Check_Type(rb_id, T_STRING);

  txt = RSTRING_PTR(rb_txt);
  txt_len = RSTRING_LEN(rb_txt);
  id = RSTRING_PTR(rb_id);
  id_len = RSTRING_LEN(rb_id);

  trans = Transliterator::createInstance(UnicodeString(id, id_len), UTRANS_FORWARD, p_error, status);
  if(!U_SUCCESS(status)) {
    rb_raise(rb_eArgError, "%s", u_errorName(status));
  }

  u_txt = new UnicodeString(txt, txt_len);
  trans->transliterate(*u_txt);
  result = u_txt->toUTF8String(result);

  delete u_txt;
  delete trans;

  rb_out = charlock_new_str(result.data(), result.length());

  return rb_out;
}

void _init_charlock_transliterator() {
  rb_cTransliterator = rb_define_class_under(rb_mCharlockHolmes, "Transliterator", rb_cObject);

  rb_define_singleton_method(rb_cTransliterator, "transliterate", (VALUE(*)(...))rb_transliterator_transliterate, 2);
}

}