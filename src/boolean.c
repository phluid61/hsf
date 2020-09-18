#include "boolean.h"

#include "types.h"
#include "errors.h"

#include <stdlib.h>

#include "error_macros.h"

/* malloc */
SH_Boolean*
SH_Boolean__init(sh_bool_t value, int* err) {
	SH_Boolean* obj = (SH_Boolean*)malloc(sizeof(SH_Boolean));

	__cascade(err, (SH_Boolean*)0);

	if ((SH_Boolean*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_Boolean*)0;
	}

	obj->value = (value == SH_FALSE ? SH_FALSE : SH_TRUE);

	__clear(err);
	return obj;
}

void
SH_Boolean__destroy(SH_Boolean* obj, int* err) {
	__cascade(err,);
	free(obj);
	__clear(err);
}

sh_bool_t
SH_Boolean__bool(SH_Boolean* obj, int* err) {
	__cascade(err, SH_FALSE);
	__clear(err);
	return obj->value;
}

sh_bool_t
SH_Boolean__true(SH_Boolean* obj, int* err) {
	__cascade(err, SH_FALSE);
	__clear(err);
	return (obj->value == SH_FALSE) ? SH_FALSE : SH_TRUE;
}

sh_bool_t
SH_Boolean__false(SH_Boolean* obj, int* err) {
	__cascade(err, SH_FALSE);
	__clear(err);
	return (obj->value == SH_FALSE) ? SH_TRUE : SH_FALSE;
}

/* malloc */
sh_char_t*
SH_Boolean__to_s(SH_Boolean* obj, int* err) {
	sh_char_t* str = (sh_char_t*)malloc(sizeof(sh_char_t) * 3);

	__cascade(err, (sh_char_t*)0);

	if ((sh_char_t*)0 == str) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (sh_char_t*)0;
	}

	str[0] = SH_CHAR_C('?');
	str[1] = SH_Boolean__true(obj, err) ? SH_CHAR_C('1') : SH_CHAR_C('0');
	str[2] = SH_CHAR_C(0);

	__clear(err);
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
