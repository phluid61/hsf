
#include "decimal.h"
#include <stdlib.h>
#include <math.h>

#define FFACTOR SH_FLOAT_C(1000.0)
#define IFACTOR UINT16_C(1000)

/* malloc */
SH_Decimal*
SH_Decimal__init(sh_float_t value) {
	SH_Decimal* obj;
	sh_bool_t n; /*negative?*/
	sh_int_t i;  /*(abs) int val*/
	uint16_t f;  /*fraction part*/

	i = (sh_int_t)value;
	if (i < 0) {
		i = -i;
		n = SH_TRUE;
	} else {
		n = SH_FALSE;
	}

	if (i > SH_INT_C(999999999999)) {
		return (SH_Decimal*)0;
	}

	/* FIXME: relies on `round` */
	f = (uint16_t)(
			(uint16_t)round(
				(sh_float_t)fabs((double)value) * FFACTOR
			) % IFACTOR
	);

	obj = (SH_Decimal*)malloc(sizeof(SH_Decimal)); /*FIXME*/
	obj->value = (n ? SH_FLOAT_C(-1.0) : SH_FLOAT_C(1.0)) * ((sh_float_t)i + ((sh_float_t)f / FFACTOR));
	obj->_neg = n;
	obj->_int = i;
	obj->_frac = f;
	return obj;
}

void
SH_Decimal__destroy(SH_Decimal* obj) {
	free(obj);
}

sh_float_t
SH_Decimal__float(SH_Decimal* obj) {
	return obj->value;
}

sh_float_t
SH_Decimal__abs(SH_Decimal* obj) {
	return (sh_float_t)fabs((double)obj->value);
}

sh_bool_t
SH_Decimal__negative(SH_Decimal* obj) {
	return obj->_neg;
}

sh_int_t
SH_Decimal__integer_part(SH_Decimal* obj) {
	return obj->_int;
}

uint16_t
SH_Decimal__fractional_part(SH_Decimal* obj) {
	return obj->_frac;
}

/* malloc */
sh_char_t*
SH_Decimal__to_s(SH_Decimal* obj) {
	sh_char_t* str;
	sh_char_t* ptr;
	sh_char_t  buffer[17]; /* sign + 15 digits + null */
	size_t n;
	sh_float_t v;

	if (obj->value == SH_FLOAT_C(0)) {
		str = (sh_char_t*)malloc(sizeof(sh_char_t) * 2); /*FIXME*/
		str[0] = (sh_char_t)'0';
		str[1] = SH_CHAR_C(0);
		return str;
	}

	n = 0;
	v = SH_Decimal__abs(obj);

	buffer[n++] = SH_CHAR_C(0);

	while (v > SH_FLOAT_C(0) && n <= 16) {
		buffer[n++] = (sh_char_t)fmod(v, SH_FLOAT_C(10)) + (sh_char_t)'0';
		v /= SH_FLOAT_C(10);
	}

	/* FIXME: if v > 0: invalid state? */

	if (SH_Decimal__negative(obj)) {
		buffer[n++] = (sh_char_t)'-';
	}

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * n); /*FIXME*/
	ptr = str;
	while (n > 0) {
		n--;
		*ptr = buffer[n];
	}

	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
