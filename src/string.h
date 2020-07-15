#ifndef _SH_STRING_H_
#define _SH_STRING_H_

#include "types.h"
#include <stdlib.h>

/* by spec this must never be less than 1024 */
#define SH_STRING_LENGTH_MAX ((size_t) 1024)

/* malloc */
SH_String*
SH_String__init(sh_char_t* value, size_t n, int* err);

void
SH_String__destroy(SH_String* obj, int* err);

size_t
SH_String__length(SH_String* obj, int* err);

/*
sh_char_t*
SH_String__string(SH_String* obj, int* err);
*/

/* malloc */
sh_char_t*
SH_String__to_s(SH_String* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
