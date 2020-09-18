#include "bytesequence.h"

#include "types.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>

#include "error_macros.h"

/* malloc */
SH_ByteSequence*
SH_ByteSequence__init(sh_byte_t* value, size_t n, int* err) {
	SH_ByteSequence* obj;

	__cascade(err, (SH_ByteSequence*)0);

	if (n > SH_BYTESEQUENCE_LENGTH_MAX) {
		__raise(err, SH_E_BYTESEQUENCE_TOO_LONG);
		return (SH_ByteSequence*)0;
	}

	obj = (SH_ByteSequence*)malloc(sizeof(SH_ByteSequence));
	if ((SH_ByteSequence*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_ByteSequence*)0;
	}

	obj->value = (sh_byte_t*)malloc(sizeof(sh_byte_t) * n);
	if ((sh_byte_t*)0 == obj->value) {
		free(obj);
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_ByteSequence*)0;
	}

	memcpy((void*)obj->value, (const void*)value, n);
	obj->length = n;

	__clear(err);
	return obj;
}

void
SH_ByteSequence__destroy(SH_ByteSequence* obj, int* err) {
	__cascade(err,);
	if ((sh_byte_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
	__clear(err);
}

/*
sh_char_t*
SH_ByteSequence__bytes(SH_ByteSequence* obj, int* err) {
	__cascade(err, (sh_char_t*)0);
	__clear(err);
	return obj->value;
}
*/

size_t
SH_ByteSequence__length(SH_ByteSequence* obj, int* err) {
	__cascade(err, (size_t)0);
	__clear(err);
	return obj->length;
}

const sh_char_t _b64[64] = {
	'A','B','C','D','E','F','G','H', 'I','J','K','L','M','N','O','P',
	'Q','R','S','T','U','V','W','X', 'Y','Z','a','b','c','d','e','f',
	'g','h','i','j','k','l','m','n', 'o','p','q','r','s','t','u','v',
	'w','x','y','z','0','1','2','3', '4','5','6','7','8','9','+','/'
};

/* malloc */
sh_char_t*
SH_ByteSequence__to_s(SH_ByteSequence* obj, int* err) {
	size_t size;
	size_t i;

	uint8_t b1;
	uint8_t b2;
	uint8_t b3;
	uint8_t b4;

	sh_char_t* str;
	sh_char_t* ptr;

	__cascade(err, (sh_char_t*)0);

	size = (obj->length * 4 + 2) / 3; /* 3in -> 4out */
	str = (sh_char_t*)malloc(sizeof(sh_char_t) * (size + 3));
	if ((sh_char_t*)0 == str) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	ptr = str;
	*ptr = SH_CHAR_C('*'); ptr ++;

	for (i = 0; i < obj->length; i += 3) {
		b1 = (obj->value[i] & 0xFC) >> 2;        /* xxxxxx__ -> __xxxxxx */
		b2 = (obj->value[i] & 0x03) << 4;        /* ______xx -> __xx____ */
		b3 = 0;
		b4 = 0;

		*ptr = _b64[b1]; ptr++;

		if ((i + 1) < obj->length) {
			b2 |= (obj->value[i+1] & 0xF0) >> 4; /* xxxx____ -> ____xxxx */
			b3  = (obj->value[i+1] & 0x0F) << 2; /* ____xxxx -> __xxxx__ */

			*ptr = _b64[b2]; ptr++;

			if ((i + 2) < obj->length) {
				b3 |= (obj->value[i+2] & 0xC0) >> 6; /* xx______ -> ______xx */
				b4  = (obj->value[i+2] & 0x3F);      /* __xxxxxx */

				*ptr = _b64[b3]; ptr++;
				*ptr = _b64[b4]; ptr++;
			} else {
				*ptr = _b64[b3]; ptr++;
				*ptr = SH_CHAR_C('='); ptr++;
			}
		} else {
			*ptr = _b64[b2]; ptr++;
			*ptr = SH_CHAR_C('='); ptr++;
			*ptr = SH_CHAR_C('='); ptr++;
		}
	}

	*ptr = SH_CHAR_C('*'); ptr ++;
	*ptr = SH_CHAR_C(0);

	__clear(err);
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
