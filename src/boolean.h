#ifndef _SH_BOOLEAN_H_
#define _SH_BOOLEAN_H_

#include "types.h"

/* malloc */
SH_Boolean*
SH_Boolean__init(sh_bool_t value, int* err);

void
SH_Boolean__destroy(SH_Boolean* obj, int* err);

sh_bool_t
SH_Boolean__bool(SH_Boolean* obj, int* err);

sh_bool_t
SH_Boolean__true(SH_Boolean* obj, int* err);

sh_bool_t
SH_Boolean__false(SH_Boolean* obj, int* err);

/* malloc */
sh_char_t*
SH_Boolean__to_s(SH_Boolean* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
