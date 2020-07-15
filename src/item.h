#ifndef _SH_ITEM_H_
#define _SH_ITEM_H_

#include "types.h"

#include <stdint.h>

SH_Item*
SH_Item__init_null(int* err);

SH_Item*
SH_Item__init_integer(SH_Integer* obj, int* err);

SH_Item*
SH_Item__init_decimal(SH_Decimal* obj, int* err);

SH_Item*
SH_Item__init_string(SH_String* obj, int* err);

SH_Item*
SH_Item__init_token(SH_Token* obj, int* err);

SH_Item*
SH_Item__init_bytesequence(SH_ByteSequence* obj, int* err);

SH_Item*
SH_Item__init_boolean(SH_Boolean* obj, int* err);

#endif
