#ifndef _SH_TOKEN_H_
#define _SH_TOKEN_H_

#include "types.h"
#include <stdlib.h>

/* by spec this must never be less than 512 */
#define SH_TOKEN_LENGTH_MAX ((size_t) 512)

/* malloc */
SH_Token*
SH_Token__init(sh_char_t* value, size_t n, int* err);

void
SH_Token__destroy(SH_Token* obj, int* err);

/*
sh_char_t*
SH_Token__string(SH_Token* obj, int* err);
*/

/* malloc */
sh_char_t*
SH_Token__to_s(SH_Token* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
