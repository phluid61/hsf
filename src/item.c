#include "item.h"

#include "types.h"
#include "errors.h"
#include "bareitem.h"
#include "key.h"
#include "_dict.h"
#include "boolean.h"

#include <stdint.h>
#include <string.h>

#include "error_macros.h"

SH_Item*
SH_Item__init(SH_BareItem* item, SH_dict* params, int* err) {
	SH_Item* obj;

	__cascade(err, (SH_Item*)0);

	obj = (SH_Item*)malloc(sizeof(SH_Item));
	if ((SH_Item*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Item*)0;
	}

	if ((SH_dict*)0 == params) {
		params = SH_dict__init(err);
		if (__catch(err)) {
			free(obj);
			return (SH_Item*)0;
		}
	}

	obj->item = item;
	obj->params = params;

	__clear(err);
	return obj;
}

void
SH_Item__destroy(SH_Item *obj, sh_bool_t recursive, int* err) {
	int local_err1 = SH_E_NO_ERROR;
	int local_err2 = SH_E_NO_ERROR;
	__cascade(err,);
	if (recursive) {
		SH_BareItem__destroy(obj->item, recursive, &local_err1);
		SH_dict__destroy(obj->params, recursive, &local_err2);
		free(obj);
		__raise(err, (SH_E_NO_ERROR == local_err1) ? local_err2 : local_err1);
	} else {
		free(obj);
		__clear(err);
	}
}

SH_BareItem*
SH_Item__item(SH_Item* obj, int* err) {
	__cascade(err, (SH_BareItem*)0);
	__clear(err);
	return obj->item;
}

SH_dict*
SH_Item__params(SH_Item* obj, int* err) {
	__cascade(err, (SH_dict*)0);
	__clear(err);
	return obj->params;
}

void
SH_Item__add_param(SH_Item* obj, SH_Key* key, SH_Item* item, int* err) {
	if (SH_dict__count(obj->params, 0) >= 256) { /* FIXME: magic numer, RFC 8941, 3.1.2 */
		__raise(err, SH_E_PARAMETERS_OVERFLOW);
		return;
	}
	SH_dict__add(obj->params, key, item, err);
}

typedef
struct __sh_item__string __sh_item__string;
struct __sh_item__string {
	size_t length;
	size_t n;
	sh_char_t* a[1024]; /* FIXME: magic number */
};

void
__SH_Item__to_s_param(SH_Key* key, SH_Item* obj, void* ptr, int* err) {
	__sh_item__string* str;

	sh_char_t* k; /* key string */
	sh_char_t* o; /* obj string */

	int local_err = SH_E_NO_ERROR;

	__cascade(err,);

	str = (__sh_item__string*)ptr;

	k = SH_Key__to_s(key, &local_err);
	if (local_err) {
		__raise(err, local_err);
		return;
	}

	if (SH_BOOLEAN == SH_BareItem__type(obj->item, &local_err) && SH_Boolean__true(SH_BareItem__get_boolean(obj->item, &local_err), &local_err)) {
		str->a[str->n ++] = k; str->length += strlen((const char*)k);
		str->a[str->n ++] = (sh_char_t*)0;
	} else {
		local_err = SH_E_NO_ERROR; /* ignore any errors above */
		o = SH_Item__to_s(obj, &local_err);
		if (local_err) {
			free(k);
			__raise(err, local_err);
			return;
		}

		str->a[str->n ++] = k; str->length += strlen((const char*)k);
		str->a[str->n ++] = o; str->length += strlen((const char*)o);
	}
}

/* malloc */
sh_char_t*
SH_Item__to_s(SH_Item* obj, int* err) {
	sh_char_t* obj_s;
	sh_char_t* tmp_s;
	sh_char_t* s;
	sh_char_t* ptr;

	size_t i;
	size_t n;
	size_t total;

	__sh_item__string str;
	str.length = (size_t)0;
	str.n = (size_t)0;

	obj_s = SH_BareItem__to_s(obj->item, err);
	__cascade(err, (sh_char_t*)0);

	SH_dict__each(obj->params, &__SH_Item__to_s_param, (void*)(&str), err);
	if (__catch(err)) {
		free(obj_s);
		for (i = 0; i < str.n; i++) {
			free(str.a[i]);
		}
		__cascade(err, (sh_char_t*)0);
	}

	n = strlen((const char*)obj_s);

	total = n;
	total += str.length;
	total += str.n; /* ';' and '=' for every pair */
	total += 1; /* NULL */

	s = (sh_char_t*)malloc(sizeof(sh_char_t) * total);
	if ((sh_char_t*)0 == s) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	ptr = s;

	if (n > 0) {
		memcpy((void*)ptr, (const void*)obj_s, n);
		free(obj_s);
		ptr += n;
	}

	for (i = 0; i < str.n; i++) {
		tmp_s = str.a[i];

		/* if the string is NULL, it was (probably) a SH_TRUE value, so don't emit anything */
		if ((sh_char_t*)0 != tmp_s) {
			*ptr = (i % 2 ? SH_CHAR_C('=') : SH_CHAR_C(';'));
			ptr ++;

			n = strlen((const char*)tmp_s);
			memcpy((void*)ptr, (const void*)tmp_s, n);
			free(str.a[i]);
			ptr += n;
		}
	}

	*ptr = SH_CHAR_C(0);

	return s;
}

/* vim: set ts=4 sts=4 sw=4: */
