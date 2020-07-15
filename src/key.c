
#include "key.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

#define __clear(v)      if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR;
#define __raise(v,code) if ((int*)0 != (v)) *(v) = (code);

/* malloc */
SH_Key*
SH_Key__init(sh_char_t* value, size_t n, int* err) {
	SH_Key* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t m;

	if (n < 1 || n > SH_KEY_LENGTH_MAX) {
		__raise(err, SH_E_KEY_TOO_LONG);
		return (SH_Key*)0;
	}

	if (*value < (sh_char_t)'a' || *value > (sh_char_t)'z') {
		__raise(err, SH_E_KEY_BAD_CHAR);
		return (SH_Key*)0;
	}

	ptr = value;
	m = 0;
	while (m < n) {
		c = *ptr;
		if (
				(c >= (sh_char_t)'a' && c <= (sh_char_t)'z') ||
				(c >= (sh_char_t)'0' && c <= (sh_char_t)'9') ||
				 c == (sh_char_t)'_' || c == (sh_char_t)'-' || c == (sh_char_t)'*') {
			ptr++;
			m++;
		} else {
			__raise(err, SH_E_KEY_BAD_CHAR);
			return (SH_Key*)0;
		}
	}

	obj = (SH_Key*)malloc(sizeof(SH_Key));
	if ((SH_Key*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Key*)0;
	}

	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (m + 1));
	if ((sh_char_t*)0 == obj->value) {
		free(obj);
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Key*)0;
	}

	memcpy((void*)obj->value, (const void*)value, m);
	obj->length = m;

	__clear(err);
	return obj;
}

void
SH_Key__destroy(SH_Key* obj, int* err) {
	if ((sh_char_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
	__clear(err);
}

/*
sh_char_t*
SH_Key__value(SH_Key* obj, int* err) {
	__clear(err);
	return obj->value;
}
*/

uint8_t
SH_Key__hash(SH_Key* obj, int* err) {
	size_t buflen;
	uint8_t* ptr;
	uint8_t hsh = UINT8_C(1);

	buflen = obj->length; /* assumes sizeof(uint8_t) and sizeof(sh_char_t) are both 1 */
	ptr = (uint8_t*)(obj->value);

	for (; buflen > 0; buflen--) {
		hsh = (hsh << 3) | (hsh >> 5);
		hsh ^= (uint8_t)*ptr;
		ptr++;
	}

	__clear(err);
	return hsh;
}

sh_bool_t
SH_Key__equal(SH_Key* obj, SH_Key* other, err) {
	size_t i;

	if (obj->length != other->length) {
		__clear(err);
		return SH_FALSE;
	}

	for (i = 0; i < obj->length; i++) {
		if (obj->value[i] != other->value[i]) {
			__clear(err);
			return SH_FALSE;
		}
	}

	__clear(err);
	return SH_TRUE;
}

/* malloc */
sh_char_t*
SH_Key__to_s(SH_Key* obj, int* err) {
	sh_char_t* str;

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (obj->length + 1)); /*FIXME*/
	if ((sh_char_t*)0 == str) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	memcpy((void*)str, (const void*)(obj->value), obj->length + 1);

	__clear(err);
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
