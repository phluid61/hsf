#ifndef _SH_STRING_H_
#define _SH_STRING_H_

#include "_types.h"
#include <string.h>

/* by spec this must never be less than 1024 */
#define SH_STRING_LENGTH_MAX ((size_t) 1024)

/* malloc */
SH_String*
SH_String__init(sh_char_t* value, size_t n);

void
SH_String__destroy(SH_String* obj);

size_t
SH_String__length(SH_String* obj);
/*
sh_char_t*
SH_String__string(SH_String* obj);
*/
/* malloc */
sh_char_t*
SH_String__to_s(SH_String* obj);

#endif
/* vim: set ts=4 sts=4 sw=4: */
