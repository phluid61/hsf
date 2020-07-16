#include "item.h"
#include "types.h"
#include "errors.h"
#include "key.h"

#include <stdint.h>

#define __clear(v)      { if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR; }
#define __raise(v,code) { if ((int*)0 != (v)) *(v) = (code); }

#define do_init(t, p, err) {                             \
	SH_BareItem* obj;                                \
                                                         \
	obj = (SH_BareItem*)malloc(sizeof(SH_BareItem)); \
	if ((SH_BareItem*)0 == obj) {                    \
		__raise(err, SH_E_MALLOC_ERROR);         \
		return (SH_BareItem*)0;                  \
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
SH_BareItem__init_integer(SH_Integer* obj, int* err) {
	do_init(SH_INTEGER, obj, err);
}

SH_BareItem*
SH_BareItem__init_decimal(SH_Decimal* obj, int* err) {
	do_init(SH_DECIMAL, obj, err);
}

SH_BareItem*
SH_BareItem__init_string(SH_String* obj, int* err) {
	do_init(SH_STRING, obj, err);
}

SH_BareItem*
SH_BareItem__init_token(SH_Token* obj, int* err) {
	do_init(SH_TOKEN, obj, err);
}

SH_BareItem*
SH_BareItem__init_bytesequence(SH_ByteSequence* obj, int* err) {
	do_init(SH_BYTESEQUENCE, obj, err);
}

SH_BareItem*
SH_BareItem__init_boolean(SH_Boolean* obj, int* err) {
	do_init(SH_BOOLEAN, obj, err);
}

