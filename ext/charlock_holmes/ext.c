#include "common.h"

extern void _init_charlock_encoding_detector();
extern void _init_charlock_converter();

VALUE rb_mCharlockHolmes;

void Init_charlock_holmes() {
	rb_mCharlockHolmes = rb_define_module("CharlockHolmes");

	_init_charlock_encoding_detector();
	_init_charlock_converter();
}