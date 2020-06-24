#ifndef _SH_KEY_H_
#define _SH_KEY_H_

#include "_types.h"
#include <string.h>

/* by spec this must never be less than 64 */
#define SH_KEY_LENGTH_MAX ((size_t) 64)

/* malloc */
SH_Key*
SH_Key__init(sh_char_t* value);

void
SH_Key__destroy(SH_Key* obj);

sh_char_t*
SH_Key__value(SH_Key* obj);

/* malloc */
sh_char_t*
SH_Key__to_s(SH_Key* obj);

#endif
/* vim: set ts=4 sts=4 sw=4: */
