
#include "bytesequence.h"
#include <stdlib.h>
#include <string.h>

/* malloc */
SH_ByteSequence*
SH_ByteSequence__init(sh_byte_t* value, size_t n) {
	SH_ByteSequence* obj;

	if (n > SH_BYTESEQUENCE_LENGTH_MAX) {
		return (SH_ByteSequence*)0;
	}

	obj = (SH_ByteSequence*)malloc(sizeof(SH_ByteSequence)); /*FIXME*/
	obj->value = (sh_byte_t*)malloc(sizeof(sh_byte_t) * n); /*FIXME*/
	memcpy((void*)obj->value, (const void*)value, n); /*FIXME*/
	obj->length = n;
	return obj;
}

void
SH_ByteSequence__destroy(SH_ByteSequence* obj) {
	if ((sh_byte_t*)0 != obj->value) {
		free(obj->value);
	}
	free(obj);
}
/*
sh_char_t*
SH_ByteSequence__bytes(SH_ByteSequence* obj) {
	return obj->value;
}
*/
size_t
SH_ByteSequence__length(SH_ByteSequence* obj) {
	return obj->length;
}

/* unsafe: c can be > 0xF */
#define _hex_nibble(c) ((c) > 9 ? ((c) - 10 + 'A') : ((c) + '0'))
#define _hex_hi(c) _hex_nibble((c & 0xF0) >> 4)
#define _hex_lo(c) _hex_nibble( c & 0x0F      )

/* malloc */
sh_char_t*
SH_ByteSequence__to_s(SH_ByteSequence* obj) {
	sh_char_t* str;
	sh_char_t* src;
	sh_char_t* dst;
	size_t i;

	str = (sh_char_t*)malloc(sizeof(sh_char_t) * obj->length * 2 + 1); /*FIXME*/
	src = obj->value;
	dst = str;
	for (i = 0; i < obj->length; i++) {
		*dst = _hex_hi(*src); dst++;
		*dst = _hex_lo(*src); dst++;
		src++;
	}
	*dst = SH_CHAR_C(0);

	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
