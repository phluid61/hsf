#include "token.h"

#include "types.h"
#include "errors.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "error_macros.h"

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
SH_Token__init(sh_char_t* value, size_t n, int* err) {
	SH_Token* obj;
	sh_char_t* ptr;
	sh_char_t  c;
	size_t m;

	__cascade(err, (SH_Token*)0);

	if (n < 1 || n > SH_TOKEN_LENGTH_MAX) {
		__raise(err, SH_E_TOKEN_TOO_LONG);
		return (SH_Token*)0;
	}

	c = *value;
	if (!LEGIT_START(c)) {
		__raise(err, SH_E_TOKEN_BAD_CHAR);
		return (SH_Token*)0;
	}

	ptr = value;
	m = 0;
	while (m < n) {
		c = *ptr;
		if (LEGIT(c)) {
			ptr++;
			m++;
		} else {
			__raise(err, SH_E_TOKEN_BAD_CHAR);
			return (SH_Token*)0;
		}
	}

	obj = (SH_Token*)malloc(sizeof(SH_Token));
	if ((SH_Token*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Token*)0;
	}

	obj->value = (sh_char_t*)malloc(sizeof(sh_char_t) * (m + 1));
	if ((sh_char_t*)0 == obj->value) {
		free(obj);
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Token*)0;
	}

	memcpy((void*)obj->value, (const void*)value, m);
	obj->value[m] = SH_CHAR_C(0);
	obj->length = m;

	__clear(err);
	return obj;
}

void
SH_Token__destroy(SH_Token* obj, int* err) {
	__cascade(err,);
	if ((sh_char_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
	__clear(err);
}

/*
sh_char_t*
SH_Token__string(SH_Token* obj, int* err) {
	__cascade(err, (sh_char_t*)0);
	__clear(err);
	return obj->value;
}
*/

/* malloc */
sh_char_t*
SH_Token__to_s(SH_Token* obj, int* err) {
	sh_char_t* str;

	__cascade(err, (sh_char_t*)0);

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
