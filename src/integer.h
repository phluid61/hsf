#ifndef _SH_INTEGER_H_
#define _SH_INTEGER_H_

#include "types.h"

#define SH_INT_MAX SH_INT_C(999999999999999)
#define SH_INT_MIN SH_INT_C(-999999999999999)

/* malloc */
SH_Integer*
SH_Integer__init(sh_int_t value, int* err);

void
SH_Integer__destroy(SH_Integer* obj, int* err);

sh_int_t
SH_Integer__int(SH_Integer* obj, int* err);

sh_bool_t
SH_Integer__negative(SH_Integer* obj, int* err);

sh_int_t
SH_Integer__abs(SH_Integer* obj, int* err);

/* malloc */
sh_char_t*
SH_Integer__to_s(SH_Integer* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
