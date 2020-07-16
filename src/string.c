#include "string.h"

#include "types.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>

#define __clear(v)      if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR;
#define __raise(v,code) if ((int*)0 != (v)) *(v) = (code);

/* malloc */
SH_String*
SH_String__init(sh_char_t* value, size_t n, int* err) {
	SH_String* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t m;

	if (n > SH_STRING_LENGTH_MAX) {
		__raise(err, SH_E_STRING_TOO_LONG);
		return (SH_String*)0;
	}

	ptr = value;
	m = 0;
	while (m < n) {
		c = *ptr;
		if (c >= SH_CHAR_C(0x20) && c <= SH_CHAR_C(0x7E)) {
			ptr++;
			m++;
		} else {
			__raise(err, SH_E_STRING_BAD_CHAR);
			return (SH_String*)0;
		}
	}

	obj = (SH_String*)malloc(sizeof(SH_String));
	if ((SH_String*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_String*)0;
	}

	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (m + 1));
	if ((sh_char_t*)0 == obj->value) {
		free(obj);
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_String*)0;
	}

	memcpy((void*)obj->value, (const void*)value, m);
	obj->value[m] = SH_CHAR_C(0);
	obj->length = m;

	__clear(err);
	return obj;
}

void
SH_String__destroy(SH_String* obj, int* err) {
	if ((sh_char_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
	__clear(err);
}

size_t
SH_String__length(SH_String* obj, int* err) {
	__clear(err);
	return obj->length;
}

/*
sh_char_t*
SH_String__string(SH_String* obj, int* err) {
	__clear(err);
	return obj->value;
}
*/

/* malloc */
sh_char_t*
SH_String__to_s(SH_String* obj, int* err) {
	sh_char_t* str;

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (obj->length + 1));
	if ((sh_char_t*)0 == str) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	memcpy((void*)str, (const void*)(obj->value), obj->length + 1);

	__clear(err);
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
