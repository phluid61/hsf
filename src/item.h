#ifndef _SH_ITEM_H_
#define _SH_ITEM_H_

#include "types.h"

#include <stdint.h>

SH_Item*
SH_Item__init(SH_BareItem* item, SH_dict* params, int* err);

void
SH_Item__destroy(SH_Item* obj, sh_bool_t recursive, int* err);

SH_BareItem*
SH_Item__item(SH_Item* obj, int* err);

SH_dict*
SH_Item__params(SH_Item* obj, int* err);

void
SH_Item__add_param(SH_Item* obj, SH_Key* key, SH_Item* item, int* err);


#endif
/* vim: set ts=4 sts=4 sw=4: */
