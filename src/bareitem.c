#include "bareitem.h"

#include "types.h"
#include "errors.h"

#include "integer.h"
#include "decimal.h"
#include "string.h"
#include "token.h"
#include "bytesequence.h"
#include "boolean.h"

#include <stdint.h>

#define __clear(v)      { if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR; }
#define __raise(v,code) { if ((int*)0 != (v)) *(v) = (code); }

#define do_init(t, p, err) {                         \
	SH_BareItem* obj;                                \
                                                     \
	obj = (SH_BareItem*)malloc(sizeof(SH_BareItem)); \
	if ((SH_BareItem*)0 == obj) {                    \
		__raise(err, SH_E_MALLOC_ERROR);             \
		return (SH_BareItem*)0;                      \
	}                                                \
                                                     \
	obj->type = t;                                   \
	obj->ptr = (void*)(p);                           \
                                                     \
	__clear(err);                                    \
	return obj;                                      \
}

SH_BareItem*
SH_BareItem__init_null(int* err) {
	do_init(SH_NULL, 0, err);
}

SH_BareItem*
SH_BareItem__init_integer(SH_Integer* value, int* err) {
	do_init(SH_INTEGER, value, err);
}

SH_BareItem*
SH_BareItem__init_decimal(SH_Decimal* value, int* err) {
	do_init(SH_DECIMAL, value, err);
}

SH_BareItem*
SH_BareItem__init_string(SH_String* value, int* err) {
	do_init(SH_STRING, value, err);
}

SH_BareItem*
SH_BareItem__init_token(SH_Token* value, int* err) {
	do_init(SH_TOKEN, value, err);
}

SH_BareItem*
SH_BareItem__init_bytesequence(SH_ByteSequence* value, int* err) {
	do_init(SH_BYTESEQUENCE, value, err);
}

SH_BareItem*
SH_BareItem__init_boolean(SH_Boolean* value, int* err) {
	do_init(SH_BOOLEAN, value, err);
}

#define do_destroy(t, obj) { \
	t ## __destroy((t*)(obj->ptr), 0); \
	free(obj); \
}

void
SH_BareItem__destroy(SH_BareItem *obj, sh_bool_t recursive, int* err) {
	if (recursive) {
		switch (obj->type) {
		case SH_NULL:
			free(obj);
			__clear(err);
			return;

		case SH_INTEGER:
			do_destroy(SH_Integer, obj);
			__clear(err);
			return;

		case SH_DECIMAL:
			do_destroy(SH_Decimal, obj);
			__clear(err);
			return;

		case SH_STRING:
			do_destroy(SH_String, obj);
			__clear(err);
			return;

		case SH_TOKEN:
			do_destroy(SH_Token, obj);
			__clear(err);
			return;

		case SH_BYTESEQUENCE:
			do_destroy(SH_ByteSequence, obj);
			__clear(err);
			return;

		case SH_BOOLEAN:
			do_destroy(SH_Boolean, obj);
			__clear(err);
			return;

		/*default: fall out */
		}

		free(obj);
		__raise(err, SH_E_ITEM_WRONG_TYPE);
	} else {
		free(obj);
		__clear(err);
	}
}

SH_Item_type
SH_BareItem__type(SH_BareItem* obj, int* err) {
	__clear(err);
	return obj->type;
}

#define do_get(obj, err, a, b) {            \
	if (a != (obj)->type) {                 \
		__raise(err, SH_E_ITEM_WRONG_TYPE); \
		return (b*)0;                       \
	}                                       \
	__clear(err);                           \
	return (b*)((obj)->ptr);                \
}

SH_Integer*
SH_BareItem__get_integer(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_INTEGER, SH_Integer);
}

SH_Decimal*
SH_BareItem__get_decimal(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_DECIMAL, SH_Decimal);
}

SH_String*
SH_BareItem__get_string(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_STRING, SH_String);
}

SH_Token*
SH_BareItem__get_token(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_TOKEN, SH_Token);
}

SH_ByteSequence*
SH_BareItem__get_bytesequence(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_BYTESEQUENCE, SH_ByteSequence);
}

SH_Boolean*
SH_BareItem__get_boolean(SH_BareItem* obj, int* err) {
	do_get(obj, err, SH_BOOLEAN, SH_Boolean);
}

sh_char_t*
SH_BareItem__to_s(SH_BareItem* obj, int* err) {
	sh_char_t* str;

	switch (obj->type) {
	case SH_NULL:
		str = (sh_char_t*)malloc(sizeof(sh_char_t));
		if ((sh_char_t*)0 == str) {
			__raise(err, SH_E_MALLOC_ERROR);
			return (sh_char_t*)0;
		}
		*str = SH_CHAR_C(0);
		return str;

	case SH_INTEGER:
		return SH_Integer__to_s((SH_Integer*)(obj->ptr), err);

	case SH_DECIMAL:
		return SH_Decimal__to_s((SH_Decimal*)(obj->ptr), err);

	case SH_STRING:
		return SH_String__to_s((SH_String*)(obj->ptr), err);

	case SH_TOKEN:
		return SH_Token__to_s((SH_Token*)(obj->ptr), err);

	case SH_BYTESEQUENCE:
		return SH_ByteSequence__to_s((SH_ByteSequence*)(obj->ptr), err);

	case SH_BOOLEAN:
		return SH_Boolean__to_s((SH_Boolean*)(obj->ptr), err);
	
	/*default: fall out */
	}

	__raise(err, SH_E_ITEM_WRONG_TYPE);
	return (sh_char_t*)0;
}

/* vim: set ts=4 sts=4 sw=4: */
