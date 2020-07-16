#ifndef _SH_BAREITEM_H_
#define _SH_BAREITEM_H_

#include "types.h"

#include <stdint.h>

SH_BareItem*
SH_BareItem__init_null(int* err);

SH_BareItem*
SH_BareItem__init_integer(SH_Integer* obj, int* err);

SH_BareItem*
SH_BareItem__init_decimal(SH_Decimal* obj, int* err);

SH_BareItem*
SH_BareItem__init_string(SH_String* obj, int* err);

SH_BareItem*
SH_BareItem__init_token(SH_Token* obj, int* err);

SH_BareItem*
SH_BareItem__init_bytesequence(SH_ByteSequence* obj, int* err);

SH_BareItem*
SH_BareItem__init_boolean(SH_Boolean* obj, int* err);

void
SH_BareItem__destroy(SH_BareItem* obj, sh_bool_t recursive, int* err);

SH_Item_type
SH_BareItem__type(SH_BareItem* obj, int* err);

SH_Integer*
SH_BareItem__get_integer(SH_BareItem* obj, int* err);

SH_Decimal*
SH_BareItem__get_decimal(SH_BareItem* obj, int* err);

SH_String*
SH_BareItem__get_string(SH_BareItem* obj, int* err);

SH_Token*
SH_BareItem__get_token(SH_BareItem* obj, int* err);

SH_ByteSequence*
SH_BareItem__get_bytesequence(SH_BareItem* obj, int* err);

SH_Boolean*
SH_BareItem__get_boolean(SH_BareItem* obj, int* err);

sh_char_t*
SH_BareItem__to_s(SH_BareItem* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
