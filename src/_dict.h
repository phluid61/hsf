#ifndef _SH_DICT_H_
#define _SH_DICT_H_

#include "types.h"

#include <stdint.h>

SH_dict_pair*
SH_dict_pair__init(SH_Key* key, SH_Item* value, int* err);

void
SH_dict_pair__destroy(SH_dict_pair* obj, sh_bool_t recursive, int* err);

SH_dict_bucket*
SH_dict_bucket__init(int* err);

void
SH_dict_bucket__destroy(SH_dict_bucket* obj, sh_bool_t recursive, int* err);

void
SH_dict_bucket__add(SH_dict_bucket* obj, SH_dict_pair* pair, int* err);

SH_dict*
SH_dict__init(int* err);

void
SH_dict__destroy(SH_dict* obj, sh_bool_t recursive, int* err);

SH_Item*
SH_dict__get(SH_dict* obj, SH_Key* key, int* err);

void
SH_dict__add(SH_dict* obj, SH_Key* key, SH_Item* item, int* err);

#endif
/* vim: set ts=4 sts=4 sw=4: */
