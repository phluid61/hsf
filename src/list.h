#ifndef _SH_List_H_
#define _SH_List_H_

#include "types.h"

#include <stdint.h>

SH_List*
SH_List__init(int* err);

void
SH_List__destroy(SH_List* obj, sh_bool_t recursive, int* err);

void
SH_List__add(SH_List* obj, SH_Item* item, int* err);

void
SH_List__each(SH_List* obj, void (*func)(SH_Item* item, void* ptr, int* err), void* ptr, int* err);

void
SH_List__each_pair(SH_List* obj, void (*func)(SH_Item* item, size_t i, void* ptr, int* err), void* ptr, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
