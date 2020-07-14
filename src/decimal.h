#ifndef _SH_DECIMAL_H_
#define _SH_DECIMAL_H_

#include "types.h"

/* malloc */
SH_Decimal*
SH_Decimal__init(sh_float_t value, int* err);

void
SH_Decimal__destroy(SH_Decimal* obj, int* err);

sh_float_t
SH_Decimal__float(SH_Decimal* obj, int* err);

sh_float_t
SH_Decimal__abs(SH_Decimal* obj, int* err);

sh_bool_t
SH_Decimal__negative(SH_Decimal* obj, int* err);

sh_int_t
SH_Decimal__integer_part(SH_Decimal* obj, int* err);

uint16_t
SH_Decimal__fractional_part(SH_Decimal* obj, int* err);

/* malloc */
sh_char_t*
SH_Decimal__to_s(SH_Decimal* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
