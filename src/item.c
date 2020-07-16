#include "item.h"

#include "types.h"
#include "errors.h"
#include "bareitem.h"
#include "_dict.h"

#include <stdint.h>

#define __clear(v)      { if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR; }
#define __raise(v,code) { if ((int*)0 != (v)) *(v) = (code); }

#define do_init(t, p, err) {                             \
}

SH_Item*
SH_Item__init(SH_BareItem* item, SH_dict* params, int* err) {
	SH_Item* obj;

	obj = (SH_Item*)malloc(sizeof(SH_Item));
	if ((SH_Item*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Item*)0;
	}

	if ((SH_dict*)0 == params) {
		params = SH_dict__init(err);
		if (err) {
			free(obj);
			return (SH_Item*)0;
		}
	}

	obj->item = item;
	obj->params = params;

	__clear(err);
	return obj;
}

SH_BareItem*
SH_Item__item(SH_Item* obj, int* err) {
	__clear(err);
	return obj->item;
}

SH_dict*
SH_Item__params(SH_Item* obj, int* err) {
	__clear(err);
	return obj->params;
}

/* vim: set ts=4 sts=4 sw=4: */
