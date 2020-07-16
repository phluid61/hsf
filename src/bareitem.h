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

#endif
