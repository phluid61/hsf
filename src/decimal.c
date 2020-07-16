
#include "decimal.h"

#include "types.h"
#include "errors.h"
#include <stdlib.h>
#include <math.h>

#define __clear(v)      if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR;
#define __raise(v,code) if ((int*)0 != (v)) *(v) = (code);

#define FFACTOR SH_FLOAT_C(1000.0)
#define IFACTOR UINT64_C(1000)

/* malloc */
SH_Decimal*
SH_Decimal__init(sh_float_t value, int* err) {
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
		__raise(err, SH_E_DECIMAL_OUT_OF_BOUNDS);
		return (SH_Decimal*)0;
	}

	/* FIXME: wrong round (to infinity, should be to even) */
	f = (uint16_t)(
			(uint64_t)(
				(sh_float_t)fabs((double)(value * FFACTOR)) + SH_FLOAT_C(0.5)
			) % IFACTOR
		);

	obj = (SH_Decimal*)malloc(sizeof(SH_Decimal));
	if ((SH_Decimal*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Decimal*)0;
	}

	obj->value = (n ? SH_FLOAT_C(-1.0) : SH_FLOAT_C(1.0)) * ((sh_float_t)i + ((sh_float_t)f / FFACTOR));
	obj->_neg = n;
	obj->_int = i;
	obj->_frac = f;

	__clear(err);
	return obj;
}

void
SH_Decimal__destroy(SH_Decimal* obj, int* err) {
	free(obj);
	__clear(err);
}

sh_float_t
SH_Decimal__float(SH_Decimal* obj, int* err) {
	__clear(err);
	return obj->value;
}

sh_float_t
SH_Decimal__abs(SH_Decimal* obj, int* err) {
	__clear(err);
	return (sh_float_t)fabs((double)obj->value);
}

sh_bool_t
SH_Decimal__negative(SH_Decimal* obj, int* err) {
	__clear(err);
	return obj->_neg;
}

sh_int_t
SH_Decimal__integer_part(SH_Decimal* obj, int* err) {
	__clear(err);
	return obj->_int;
}

uint16_t
SH_Decimal__fractional_part(SH_Decimal* obj, int* err) {
	__clear(err);
	return obj->_frac;
}

/* malloc */
sh_char_t*
SH_Decimal__to_s(SH_Decimal* obj, int* err) {
	sh_char_t* str;
	sh_char_t* ptr;
	sh_char_t  buffer[18]; /* sign + 12 digits + dot + 3 digits + null */
	size_t n;
	sh_int_t v;

	if (obj->value == SH_FLOAT_C(0)) {
		str = (sh_char_t*)malloc(sizeof(sh_char_t) * 4);
		if ((sh_char_t*)0 == str) {
			__raise(err, SH_E_MALLOC_ERROR);
			return (sh_char_t*)0;
		}

		str[0] = (sh_char_t)'0';
		str[1] = (sh_char_t)'.';
		str[2] = (sh_char_t)'0';
		str[3] = SH_CHAR_C(0);

		__clear(err);
		return str;
	}

	n = 0;
	buffer[n++] = SH_CHAR_C(0);

	/* fractional part */
	v = (sh_int_t)SH_Decimal__fractional_part(obj, err);

	if (SH_INT_C(0) == v) {
		buffer[n++] = SH_CHAR_C('0');
	} else {
		while (v > SH_INT_C(0)) {
			buffer[n++] = (sh_char_t)(v % 10) + SH_CHAR_C('0');
			v /= SH_INT_C(10);
		}
	}

	buffer[n++] = SH_CHAR_C('.');

	/* integer part and sign (same as SH_Integer) */
	v = SH_Decimal__integer_part(obj, err);

	while (v > SH_INT_C(0) && n <= 14) {
		buffer[n++] = (sh_char_t)(v % 10) + SH_CHAR_C('0');
		v /= SH_INT_C(10);
	}

	/* FIXME: if v > 0: invalid state? */

	if (SH_Decimal__negative(obj, err)) {
		buffer[n++] = (sh_char_t)'-';
	}

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * n);
	if ((sh_char_t*)0 == str) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	ptr = str;
	while (n > 0) {
		n--;
		*ptr = buffer[n];
		ptr++;
	}

	__clear(err);
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
