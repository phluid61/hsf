
#include "integer.h"
#include <stdlib.h>

/* malloc */
SH_Integer*
SH_Integer__init(sh_int_t value) {
	SH_Integer* obj;

	if (value < SH_INT_MIN || value > SH_INT_MAX) {
		return (SH_Integer*)0;
	}

	obj = (SH_Integer*)malloc(sizeof(SH_Integer)); /*FIXME*/
	obj->value = value;
	return obj;
}

void
SH_Integer__destroy(SH_Integer* obj) {
	free(obj);
}

sh_int_t
SH_Integer__int(SH_Integer* obj) {
	return obj->value;
}

sh_bool_t
SH_Integer__negative(SH_Integer* obj) {
	return (sh_bool_t)(obj->value < SH_INT_C(0));
}

sh_int_t
SH_Integer__abs(SH_Integer* obj) {
	if (SH_Integer__negative(obj)) {
		return -(obj->value);
	} else {
		return obj->value;
	}
}

/* malloc */
sh_char_t*
SH_Integer__to_s(SH_Integer* obj) {
	sh_char_t* str;
	sh_char_t* ptr;
	sh_char_t  buffer[17]; /* sign + 15 digits + null */
	size_t n;
	sh_int_t v;

	if (obj->value == SH_INT_C(0)) {
		str = (sh_char_t*)malloc(sizeof(sh_char_t) * 2); /*FIXME*/
		str[0] = (sh_char_t)'0';
		str[1] = SH_CHAR_C(0);
		return str;
	}

	n = 0;
	v = SH_Integer__abs(obj);

	buffer[n++] = SH_CHAR_C(0);

	while (v > SH_INT_C(0) && n <= 16) {
		buffer[n++] = (sh_char_t)(v % 10) + (sh_char_t)'0';
		v /= SH_INT_C(10);
	}

	/* FIXME: if v > 0: invalid state? */

	if (SH_Integer__negative(obj)) {
		buffer[n++] = (sh_char_t)'-';
	}

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * n); /*FIXME*/
	ptr = str;
	while (n > 0) {
		n--;
		*ptr = buffer[n];
		ptr++;
	}

	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
