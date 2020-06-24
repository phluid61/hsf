#ifndef _SH_BYTESEQUENCE_H_
#define _SH_BYTESEQUENCE_H_

#include "_types.h"
#include <string.h>
#include <stdlib.h>

/* by spec this must never be less than 16384 */
#define SH_BYTESEQUENCE_LENGTH_MAX ((size_t) 16384)

/* malloc */
SH_ByteSequence*
SH_ByteSequence__init(sh_byte_t* value, size_t n);

void
SH_ByteSequence__destroy(SH_ByteSequence* obj);

sh_byte_t*
SH_ByteSequence__bytes(SH_ByteSequence* obj);

size_t
SH_ByteSequence__length(SH_ByteSequence* obj);

/* malloc */
sh_char_t*
SH_ByteSequence__to_s(SH_ByteSequence* obj);

#endif
/* vim: set ts=4 sts=4 sw=4: */
