#include "innerlist.h"

#include "types.h"
#include "errors.h"
#include "item.h"

#include <stdint.h>
#include <string.h>

#include "error_macros.h"

SH_InnerList*
SH_InnerList__init(int* err) {
	SH_InnerList* obj;

	__cascade(err, (SH_InnerList*)0);

	obj = (SH_InnerList*)malloc(sizeof(SH_InnerList));
	if ((SH_InnerList*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_InnerList*)0;
	}

	obj->count = 0;

	__clear(err);
	return obj;
}

void
SH_InnerList__destroy(SH_InnerList* obj, sh_bool_t recursive, int* err) {
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
SH_InnerList__add(SH_InnerList* obj, SH_Item* item, int* err) {
	__cascade(err,);
	if (obj->count >= SH_INNERLIST_CAPACITY) {
		__raise(err, SH_E_LIST_OVERFLOW);
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
SH_InnerList__each(SH_InnerList* obj, void (*func)(SH_Item* item, void* ptr, int* err), void* ptr, int* err) {
	__each(obj, err, item, ptr);
}

void
SH_InnerList__each_pair(SH_InnerList* obj, void (*func)(SH_Item* item, size_t i, void* ptr, int* err), void* ptr, int* err) {
	__each(obj, err, item, i, ptr);
}

typedef
struct __SH_InnerList__string __SH_InnerList__string;
struct __SH_InnerList__string {
	size_t length;
	size_t n;
	sh_char_t* a[SH_INNERLIST_CAPACITY];
};

void
__SH_InnerList__to_s_item(SH_Item* obj, void* ptr, int* err) {
	__SH_InnerList__string* str;

	sh_char_t* s;

	int local_err = SH_E_NO_ERROR;

	__cascade(err,);

	str = (__SH_InnerList__string*)ptr;

	s = SH_Item__to_s(obj, &local_err);
	if (local_err) {
		__raise(err, local_err);
		return;
	}

	str->a[str->n ++] = s; str->length += strlen((const char*)s);
}

/*malloc*/
sh_char_t*
SH_InnerList__to_s(SH_InnerList* obj, int* err) {
	sh_char_t* tmp_s;
	sh_char_t* s;
	sh_char_t* ptr;

	size_t i;
	size_t n;
	size_t total;

	__SH_InnerList__string str;
	str.length = (size_t)0;
	str.n = (size_t)0;

	SH_InnerList__each(obj, &__SH_InnerList__to_s_item, (void*)(&str), err);
	if (__catch(err)) {
		for (i = 0; i < str.n; i++) {
			free(str.a[i]);
		}
		__cascade(err, (sh_char_t*)0);
	}

	total = 2; /* '(' and ')' */
	total += str.length;
	if (str.n > 1)
		total += (str.n - 1); /* ' ' between items */
	total += 1; /* NULL */

	s = (sh_char_t*)malloc(sizeof(sh_char_t) * total);
	if ((sh_char_t*)0 == s) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	ptr = s;

	*ptr = '(';
	ptr ++;

	for (i = 0; i < str.n; i++) {
		if (i > 0) {
			*ptr = ' ';
			ptr ++;
		}

		tmp_s = str.a[i];
		n = strlen((const char*)tmp_s);
		memcpy((void*)ptr, (const void*)tmp_s, n);
		free(str.a[i]);
		ptr += n;
	}

	*ptr = ')';
	ptr ++;

	*ptr = SH_CHAR_C(0);

	return s;
}

/* vim: set ts=4 sts=4 sw=4: */
