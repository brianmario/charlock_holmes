#include "ruby.h"
#include "unicode/ucsdet.h"

#define CHARLOCK_HOLMES_VERSION "0.2.0"

static VALUE rb_mCharlockHolmes;
static VALUE rb_cEncodingDetector;

static VALUE rb_encdec_buildmatch(const UCharsetMatch *match)
{
	UErrorCode status = U_ZERO_ERROR;
	const char *mname;
	const char *mlang;
	int mconfidence;
	VALUE rb_match;

	if (!match)
		return Qnil;

	mname = ucsdet_getName(match, &status);
	mlang = ucsdet_getLanguage(match, &status);
	mconfidence = ucsdet_getConfidence(match, &status);

	rb_match = rb_hash_new();

	rb_hash_aset(rb_match, ID2SYM(rb_intern("encoding")), rb_str_new2(mname));
	rb_hash_aset(rb_match, ID2SYM(rb_intern("confidence")), INT2NUM(mconfidence));

	if (mlang && mlang[0])
		rb_hash_aset(rb_match, ID2SYM(rb_intern("language")), rb_str_new2(mlang));

	return rb_match;
}

/*
 * call-seq: detection_hash = EncodingDetector.detect "some string"
 *
 * Attempt to detect the encoding of this string
 *
 * Returns: a Hash with :encoding, :language and :confidence
 */
static VALUE rb_encdec_detect(VALUE self, VALUE rb_str)
{
	UErrorCode status = U_ZERO_ERROR;
	UCharsetDetector *csd;

	Check_Type(rb_str, T_STRING);
	Data_Get_Struct(self, UCharsetDetector, csd);

	ucsdet_setText(csd, RSTRING_PTR(rb_str), (int32_t)RSTRING_LEN(rb_str), &status);
	return rb_encdec_buildmatch(ucsdet_detect(csd, &status));
}


/*
 * call-seq: detection_hash_array = EncodingDetector.detect_all "some string"
 *
 * Attempt to detect the encoding of this string, and return
 * a list with all the possible encodings that match it.
 *
 * Returns: a List with zero or more Hashes,
 *	each one of them with with :encoding, :language and :confidence
 */
static VALUE rb_encdec_detect_all(VALUE self, VALUE rb_str)
{
	UErrorCode status = U_ZERO_ERROR;
	UCharsetDetector *csd;
    const UCharsetMatch **csm;
	VALUE rb_ret;
	int i, match_count;

	Check_Type(rb_str, T_STRING);
	Data_Get_Struct(self, UCharsetDetector, csd);

	rb_ret = rb_ary_new();

	ucsdet_setText(csd, RSTRING_PTR(rb_str), (int32_t)RSTRING_LEN(rb_str), &status);
    csm = ucsdet_detectAll(csd, &match_count, &status);

	for (i = 0; i < match_count; ++i) {
		rb_ary_push(rb_ret, rb_encdec_buildmatch(csm[i]));
	}

	return rb_ret;
}


static void rb_encdec__free(void *csd)
{
	ucsdet_close((UCharsetDetector *)csd);
}

static VALUE rb_encdec__alloc(VALUE klass)
{
	UErrorCode status = U_ZERO_ERROR;
	UCharsetDetector *csd = ucsdet_open(&status);
	return Data_Wrap_Struct(klass, NULL, rb_encdec__free, (void *)csd);
}

static VALUE rb_encdec_initialize(VALUE self)
{
	return Qnil;
}

void Init_charlock_holmes()
{
	rb_mCharlockHolmes = rb_define_module("CharlockHolmes");
	rb_define_const(rb_mCharlockHolmes, "VERSION", rb_str_new2(CHARLOCK_HOLMES_VERSION));

	rb_cEncodingDetector = rb_define_class_under(rb_mCharlockHolmes, "EncodingDetector", rb_cObject);
	rb_define_alloc_func(rb_cEncodingDetector, rb_encdec__alloc);
	rb_define_method(rb_cEncodingDetector, "initialize", rb_encdec_initialize, 0);
	rb_define_method(rb_cEncodingDetector, "detect", rb_encdec_detect, 1);
	rb_define_method(rb_cEncodingDetector, "detect_all", rb_encdec_detect_all, 1);
}
