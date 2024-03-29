#ifndef _SH_DICT_H_
#define _SH_DICT_H_

#include "types.h"

#include <stdint.h>

SH_dict*
SH_dict__init(int* err);

void
SH_dict__destroy(SH_dict* obj, sh_bool_t recursive, int* err);

SH_Item*
SH_dict__get(SH_dict* obj, SH_Key* key, int* err);

size_t
SH_dict__count(SH_dict* obj, int* err);

void
SH_dict__add(SH_dict* obj, SH_Key* key, SH_Item* item, int* err);

void
SH_dict__each(SH_dict* obj, void (*func)(SH_Key* key, SH_Item* item, void* ptr, int* err), void* ptr, int* err);

void
SH_dict__each_key(SH_dict* obj, void (*func)(SH_Key* key, void* ptr, int* err), void* ptr, int* err);

void
SH_dict__each_item(SH_dict* obj, void (*func)(SH_Item* item, void* ptr, int* err), void* ptr, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
