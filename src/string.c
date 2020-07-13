
#include "string.h"
#include <stdlib.h>
#include <string.h>

/* malloc */
SH_String*
SH_String__init(sh_char_t* value, size_t n) {
	SH_String* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t m;

	if (n > SH_STRING_LENGTH_MAX) {
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
			return (SH_String*)0;
		}
	}

	obj = (SH_String*)malloc(sizeof(SH_String)); /*FIXME*/
	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (m + 1)); /*FIXME*/
	memcpy((void*)obj->value, (const void*)value, m); /*FIXME*/
	obj->value[m] = SH_CHAR_C(0);
	obj->length = m;
	return obj;
}

void
SH_String__destroy(SH_String* obj) {
	if ((sh_char_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
}

size_t
SH_String__length(SH_String* obj) {
	return obj->length;
}
/*
sh_char_t*
SH_String__string(SH_String* obj) {
	return obj->value;
}
*/
/* malloc */
sh_char_t*
SH_String__to_s(SH_String* obj) {
	sh_char_t* str;
	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (obj->length + 1)); /*FIXME*/
	memcpy((void*)str, (const void*)(obj->value), obj->length + 1); /*FIXME*/
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
