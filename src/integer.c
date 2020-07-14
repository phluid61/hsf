
#include "integer.h"
#include "errors.h"
#include <stdlib.h>

#define __clear(v)      if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR;
#define __raise(v,code) if ((int*)0 != (v)) *(v) = (code);

/* malloc */
SH_Integer*
SH_Integer__init(sh_int_t value, int* err) {
	SH_Integer* obj;

	if (value < SH_INT_MIN || value > SH_INT_MAX) {
		__raise(err, SH_E_INTEGER_OUT_OF_BOUNDS);
		return (SH_Integer*)0;
	}

	obj = (SH_Integer*)malloc(sizeof(SH_Integer));
	if ((SH_Integer*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Integer*)0;
	}

	obj->value = value;

	__clear(err);
	return obj;
}

void
SH_Integer__destroy(SH_Integer* obj, int* err) {
	free(obj);
	__clear(err);
}

sh_int_t
SH_Integer__int(SH_Integer* obj, int* err) {
	__clear(err);
	return obj->value;
}

sh_bool_t
SH_Integer__negative(SH_Integer* obj, int* err) {
	__clear(err);
	return (sh_bool_t)(obj->value < SH_INT_C(0));
}

sh_int_t
SH_Integer__abs(SH_Integer* obj, int* err) {
	if (SH_Integer__negative(obj, err)) {
		__clear(err);
		return -(obj->value);
	} else {
		__clear(err);
		return obj->value;
	}
}

/* malloc */
sh_char_t*
SH_Integer__to_s(SH_Integer* obj, int* err) {
	sh_char_t* str;
	sh_char_t* ptr;
	sh_char_t  buffer[17]; /* sign(1) + digits(15) + null(1) */
	size_t n;
	sh_int_t v;

	if (obj->value == SH_INT_C(0)) {
		str = (sh_char_t*)malloc(sizeof(sh_char_t) * 2);
		if ((sh_char_t*)0 == str) {
			__raise(err, SH_E_MALLOC_ERROR);
			return (sh_char_t*)0;
		}

		str[0] = (sh_char_t)'0';
		str[1] = SH_CHAR_C(0);
		__clear(err);
		return str;
	}

	n = 0;
	v = SH_Integer__abs(obj, err);

	buffer[n++] = SH_CHAR_C(0);

	while (v > SH_INT_C(0) && n <= 16) {
		buffer[n++] = (sh_char_t)(v % 10) + (sh_char_t)'0';
		v /= SH_INT_C(10);
	}

	/* FIXME: if v > 0: invalid state? */

	if (SH_Integer__negative(obj, err)) {
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
