#include "common.h"
#undef UChar

#include "unicode/ucnv.h"
#include "unicode/utrans.h"

extern VALUE rb_mCharlockHolmes;
static VALUE rb_cConverter;

static VALUE rb_converter_convert(VALUE self, VALUE rb_txt, VALUE rb_src_enc, VALUE rb_dst_enc) {
	VALUE rb_out;
	const char *src_enc;
	const char *dst_enc;
	const char *src_txt;
	char *out_buf;
	void *rb_enc = NULL;
	int32_t src_len;
	int32_t out_len;
	UErrorCode status = U_ZERO_ERROR;

	Check_Type(rb_txt, T_STRING);
	Check_Type(rb_src_enc, T_STRING);
	Check_Type(rb_dst_enc, T_STRING);

	src_txt = RSTRING_PTR(rb_txt);
	src_len = RSTRING_LEN(rb_txt);
	src_enc = RSTRING_PTR(rb_src_enc);
	dst_enc = RSTRING_PTR(rb_dst_enc);

	// first determin the size of the output buffer
	out_len = ucnv_convert(dst_enc, src_enc, NULL, 0, src_txt, src_len, &status);
	if (status != U_BUFFER_OVERFLOW_ERROR) {
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}
	out_buf = malloc(out_len);

	// now do the actual conversion
	status = U_ZERO_ERROR;
	out_len = ucnv_convert(dst_enc, src_enc, out_buf, out_len, src_txt, src_len, &status);
	if (!U_SUCCESS(status)) {
		free(out_buf);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

#ifdef HAVE_RUBY_ENCODING_H
	rb_enc = (void *)rb_enc_find(dst_enc);
#endif

	rb_out = charlock_new_enc_str(out_buf, out_len, rb_enc);

	free(out_buf);

	return rb_out;
}

// The return value needs to be freed later
static inline UChar *cstr_to_uchar(const char *src, int32_t src_len, int32_t *out_len) {
	UErrorCode status;
	UChar *dst_uchars;
	UConverter *utf8_conv;
	int32_t dst_uchar_len;

	status = U_ZERO_ERROR;
	// grab a UTF-8 converter
	utf8_conv = ucnv_open("UTF-8", &status);
	if (!U_SUCCESS(status)) {
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	status = U_ZERO_ERROR;
	// get the size of the buffer needed for the char -> UChar conversion
	dst_uchar_len = ucnv_toUChars(utf8_conv, NULL, 0, src, src_len, &status);
	if (status != U_BUFFER_OVERFLOW_ERROR) {
		ucnv_close(utf8_conv);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}
	*out_len = dst_uchar_len;
	dst_uchars = malloc(dst_uchar_len);

	status = U_ZERO_ERROR;
	// actually do the char -> UChar conversion
	dst_uchar_len = ucnv_toUChars(utf8_conv, dst_uchars, dst_uchar_len, src, src_len, &status);
	if (!U_SUCCESS(status)) {
		ucnv_close(utf8_conv);
		free(dst_uchars);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	ucnv_close(utf8_conv);
	return dst_uchars;
}

// The return value needs to be freed later
static inline char *uchar_to_cstr(UChar *src, int32_t src_len, int32_t *out_len) {
	UErrorCode status;
	UConverter *utf8_conv;
	char *dst_cstr;
	int32_t dst_cstr_len;

	status = U_ZERO_ERROR;
	// grab a UTF-8 converter
	utf8_conv = ucnv_open("UTF-8", &status);
	if (!U_SUCCESS(status)) {
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	status = U_ZERO_ERROR;
	// get the size of the buffer needed for the UChar -> char conversion
	dst_cstr_len = ucnv_fromUChars(utf8_conv, NULL, 0, src, src_len, &status);
	if (status != U_BUFFER_OVERFLOW_ERROR) {
		ucnv_close(utf8_conv);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}
	*out_len = dst_cstr_len;
	dst_cstr = malloc(dst_cstr_len);

	status = U_ZERO_ERROR;
	// actually do the UChar -> char conversion
	dst_cstr_len = ucnv_fromUChars(utf8_conv, dst_cstr, dst_cstr_len, src, src_len, &status);
	if (!U_SUCCESS(status)) {
		ucnv_close(utf8_conv);
		free(dst_cstr);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	ucnv_close(utf8_conv);
	return dst_cstr;
}

static VALUE rb_converter_transliterate(VALUE self, VALUE rb_txt, VALUE rb_trans_id) {
	VALUE rb_out;
	UChar *uchar_id;
	int32_t uchar_id_len;
	UChar *uchar_txt;
	int32_t uchar_txt_len;
	const char *src_txt;
	int32_t src_len;
	const char *id_txt;
	int32_t id_len;
	UErrorCode status;
	UTransliterator *trans;
	char *out_txt;
	int32_t out_len;
	int32_t limit;
	void *rb_enc = NULL;

	Check_Type(rb_txt, T_STRING);
	Check_Type(rb_trans_id, T_STRING);

	src_txt = RSTRING_PTR(rb_txt);
	src_len = RSTRING_LEN(rb_txt);
	id_txt = RSTRING_PTR(rb_trans_id);
	id_len = RSTRING_LEN(rb_trans_id);

	status = U_ZERO_ERROR;
	uchar_id = cstr_to_uchar(id_txt, id_len, &uchar_id_len);

	// TODO: track UParseError parameter
	trans = utrans_openU(uchar_id, uchar_id_len, UTRANS_FORWARD, NULL, 0, NULL, &status);
	if (!U_SUCCESS(status)) {
		free(uchar_id);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	status = U_ZERO_ERROR;
	uchar_txt = cstr_to_uchar(src_txt, src_len, &uchar_txt_len);
	limit = uchar_txt_len;

	utrans_transUChars(trans, uchar_txt, &uchar_txt_len, uchar_txt_len, 0, &limit, &status);
	if (!U_SUCCESS(status)) {
		free(uchar_id);
		free(uchar_txt);
		rb_raise(rb_eArgError, "%s", u_errorName(status));
	}

	status = U_ZERO_ERROR;
	out_txt = uchar_to_cstr(uchar_txt, uchar_txt_len, &out_len);

#ifdef HAVE_RUBY_ENCODING_H
	rb_enc = (void *)rb_utf8_encoding();
#endif

	rb_out = charlock_new_enc_str(out_txt, out_len, rb_enc);

	utrans_close(trans);
	free(uchar_id);
	free(uchar_txt);
	free(rb_out);

	return rb_out;
}

void _init_charlock_converter() {
	rb_cConverter = rb_define_class_under(rb_mCharlockHolmes, "Converter", rb_cObject);

	rb_define_singleton_method(rb_cConverter, "convert", rb_converter_convert, 3);
	rb_define_singleton_method(rb_cConverter, "transliterate", rb_converter_transliterate, 2);
}
