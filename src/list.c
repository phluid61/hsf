#include "list.h"

#include "types.h"
#include "errors.h"
#include "item.h"

#include <stdint.h>

#include "error_macros.h"

SH_List*
SH_List__init(int* err) {
	SH_List* obj;

	__cascade(err, (SH_List*)0);

	obj = (SH_List*)malloc(sizeof(SH_List));
	if ((SH_List*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_List*)0;
	}

	obj->count = 0;

	__clear(err);
	return obj;
}

void
SH_List__destroy(SH_List* obj, sh_bool_t recursive, int* err) {
	int local_err;
	int final_err = SH_E_NO_ERROR;
	size_t i;
	__cascade(err,);
	if (recursive) {
		for (i = 0; i < obj->count; i++) {
			local_err = SH_E_NO_ERROR;
			SH_Item__destroy(obj->_list[i], recursive, &local_err);
			if (final_err == SH_E_NO_ERROR && local_err != SH_E_NO_ERROR) {
				final_err = local_err;
			}
		}
		free(obj);
		__raise(err, final_err);
	} else {
		free(obj);
		__clear(err);
	}
}

void
SH_List__add(SH_List* obj, SH_Item* item, int* err) {
	__cascade(err,);
	if (obj->count >= SH_LIST_CAPACITY) {
		__raise(err, SH_E_KEY_LIST_OVERFLOW);
		return;
	}
	obj->_list[obj->count++] = item;
	__clear(err);
}

#define __each(obj, err, ...) {           \
    SH_Item* item;                        \
	size_t i;                             \
	__cascade(err,);                      \
	for (i = 0; i < obj->count; i++) {    \
		item = obj->_list[i];             \
		(*func)(__VA_ARGS__, err);        \
		__cascade(err,);                  \
	}                                     \
}

void
SH_List__each(SH_List* obj, void (*func)(SH_Item* item, void* ptr, int* err), void* ptr, int* err) {
	__each(obj, err, item, ptr);
}

void
SH_List__each_pair(SH_List* obj, void (*func)(SH_Item* item, size_t i, void* ptr, int* err), void* ptr, int* err) {
	__each(obj, err, item, i, ptr);
}

/* vim: set ts=4 sts=4 sw=4: */
