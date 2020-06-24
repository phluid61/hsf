
#include "key.h"
#include <stdlib.h>
#include <string.h>

/* malloc */
SH_Key*
SH_Key__init(sh_char_t* value) {
	SH_Key* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t n;

	if (value == (sh_char_t*)0) {
		return (SH_Key*)0;
	}

	if (*value < (sh_char_t)'a' || *value > (sh_char_t)'z') {
		return (SH_Key*)0;
	}

	ptr = value;
	n = 0;
	while ((c = *ptr) != SH_CHAR_C(0) && n <= SH_KEY_LENGTH_MAX) {
		if (
				(c >= (sh_char_t)'a' && c <= (sh_char_t)'z') ||
				(c >= (sh_char_t)'0' && c <= (sh_char_t)'9') ||
				 c == (sh_char_t)'_' || c == (sh_char_t)'-' || c == (sh_char_t)'*') {
			ptr++;
			n++;
		} else {
			return (SH_Key*)0;
		}
	}

	if (n > SH_KEY_LENGTH_MAX) {
		return (SH_Key*)0;
	}

	obj = (SH_Key*)malloc(sizeof(SH_Key)); /*FIXME*/
	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (n + 1)); /*FIXME*/
	memcpy((void*)obj->value, (const void*)value, n); /*FIXME*/
	obj->length = n;
	return obj;
}

void
SH_Key__destroy(SH_Key* obj) {
	free(obj->value);
	free(obj);
}

sh_char_t*
SH_Key__value(SH_Key* obj) {
	return obj->value;
}

/* malloc */
sh_char_t*
SH_Key__to_s(SH_Key* obj) {
	sh_char_t* str;
	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (obj->length + 1)); /*FIXME*/
	memcpy((void*)str, (const void*)(obj->value), obj->length + 1); /*FIXME*/
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
