
#include "token.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* FIXME: these don't work with non-ASCII (high-bit set) chars */

#define LEGIT_START(c) ( \
 ((sh_char_t)(c) >= SH_CHAR_C(64)) ? \
 ((UINT64_C(1) << ((sh_char_t)(c) - SH_CHAR_C(64))) & UINT64_C(0x07FFFFFE07FFFFFE)) : \
 ((UINT64_C(1) <<  (sh_char_t)(c)                 ) & UINT64_C(0x0000040000000000)) \
)

#define LEGIT(c) ( \
 ((sh_char_t)(c) >= SH_CHAR_C(64)) ? \
 ((UINT64_C(1) << ((sh_char_t)(c) - SH_CHAR_C(64))) & UINT64_C(0x57FFFFFFC7FFFFFE)) : \
 ((UINT64_C(1) <<  (sh_char_t)(c)                 ) & UINT64_C(0x07FFECFA00000000)) \
)

/* malloc */
SH_Token*
SH_Token__init(sh_char_t* value) {
	SH_Token* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t n;

	if (value == (sh_char_t*)0) {
		return (SH_Token*)0;
	}

	c = *value;
	if (!LEGIT_START(c)) {
		return (SH_Token*)0;
	}

	ptr = value;
	n = 0;
	while ((c = *ptr) != SH_CHAR_C(0) && n <= SH_TOKEN_LENGTH_MAX) {
		if (LEGIT(c)) {
			ptr++;
			n++;
		} else {
			return (SH_Token*)0;
		}
	}

	if (n > SH_TOKEN_LENGTH_MAX) {
		return (SH_Token*)0;
	}

	obj = (SH_Token*)malloc(sizeof(SH_Token)); /*FIXME*/
	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (n + 1)); /*FIXME*/
	memcpy((void*)obj->value, (const void*)value, n + 1); /*FIXME*/
	obj->length = n;
	return obj;
}

void
SH_Token__destroy(SH_Token* obj) {
	free(obj->value);
	free(obj);
}

sh_char_t*
SH_Token__string(SH_Token* obj) {
	return obj->value;
}

/* malloc */
sh_char_t*
SH_Token__to_s(SH_Token* obj) {
	sh_char_t* str;
	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (obj->length + 1)); /*FIXME*/
	memcpy((void*)str, (const void*)(obj->value), obj->length + 1); /*FIXME*/
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
