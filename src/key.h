#ifndef _SH_KEY_H_
#define _SH_KEY_H_

#include "types.h"
#include <stdlib.h>
#include <stdint.h>

/* by spec this must never be less than 64 */
#define SH_KEY_LENGTH_MAX ((size_t) 64)

/* malloc */
SH_Key*
SH_Key__init(sh_char_t* value, size_t n, int* err);

void
SH_Key__destroy(SH_Key* obj, int* err);

/*
sh_char_t*
SH_Key__value(SH_Key* obj, int* err);
*/

uint8_t
SH_Key__hash(SH_Key* obj, int* err);

sh_bool_t
SH_Key__equal(SH_Key* obj, SH_Key* other, int* err);

/* malloc */
sh_char_t*
SH_Key__to_s(SH_Key* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
