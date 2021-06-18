#ifndef _SH_InnerList_H_
#define _SH_InnerList_H_

#include "types.h"

#include <stdint.h>

SH_InnerList*
SH_InnerList__init(int* err);

void
SH_InnerList__destroy(SH_InnerList* obj, sh_bool_t recursive, int* err);

void
SH_InnerList__add(SH_InnerList* obj, SH_Item* item, int* err);

void
SH_InnerList__each(SH_InnerList* obj, void (*func)(SH_Item* item, void* ptr, int* err), void* ptr, int* err);

void
SH_InnerList__each_pair(SH_InnerList* obj, void (*func)(SH_Item* item, size_t i, void* ptr, int* err), void* ptr, int* err);

/*malloc*/
sh_char_t*
SH_InnerList__to_s(SH_InnerList* obj, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
