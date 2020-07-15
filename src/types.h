#ifndef _SH_TYPES_H_
#define _SH_TYPES_H_

#include <stdint.h>
#include <stdlib.h>

#define sh_bool_t    uint8_t
#define SH_BOOL_C(x) UINT8_C(x)

#define sh_byte_t    uint8_t
#define SH_BYTE_C(x) UINT8_C(x)

#define sh_char_t    uint8_t
#define SH_CHAR_C(x) UINT8_C(x)

#define sh_float_t   double
#define SH_FLOAT_C(x) ((double) x)

#define sh_int_t     int64_t
#define SH_INT_C(x)  INT64_C(x)

#define SH_TRUE  SH_BOOL_C(-1)
#define SH_FALSE SH_BOOL_C(0)

typedef enum {
	SH_NULL = 0, /* no item */

	SH_INTEGER,
	SH_DECIMAL,
	SH_STRING,
	SH_TOKEN,
	SH_BYTESEQUENCE,
	SH_BOOLEAN,

	SH_INNERLIST /* special case */
} SH_Item_type;

typedef struct SH_Item {
	SH_Item_type type;
	void* ptr;
} SH_Item;

typedef struct SH_Boolean {
	sh_bool_t value;
} SH_Boolean;

typedef struct SH_ByteSequence {
	sh_byte_t *value;
	size_t     length;
} SH_ByteSequence;

typedef struct SH_Decimal {
	sh_float_t value;
	sh_bool_t  _neg;
	sh_int_t   _int;
	uint16_t   _frac;
} SH_Decimal;

typedef struct SH_Integer {
	sh_int_t value;
} SH_Integer;

typedef struct SH_Key {
	sh_char_t *value;
	size_t     length;
} SH_Key;

typedef struct SH_String {
	sh_char_t *value;
	size_t     length;
} SH_String;

typedef struct SH_Token {
	sh_char_t *value;
	size_t     length;
} SH_Token;

#endif
/* vim: set ts=4 sts=4 sw=4: */
