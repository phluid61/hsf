
#include "boolean.h"
#include <stdlib.h>

/* malloc */
SH_Boolean*
SH_Boolean__init(sh_bool_t value) {
	SH_Boolean* obj = (SH_Boolean*)malloc(sizeof(SH_Boolean)); /*FIXME*/
	obj->value = (value == SH_FALSE ? SH_FALSE : SH_TRUE);
	return obj;
}

void
SH_Boolean__destroy(SH_Boolean* obj) {
	free(obj);
}

sh_bool_t
SH_Boolean__bool(SH_Boolean* obj) {
	return obj->value;
}

sh_bool_t
SH_Boolean__true(SH_Boolean* obj) {
	return (obj->value != SH_FALSE);
}

sh_bool_t
SH_Boolean__false(SH_Boolean* obj) {
	return (obj->value == SH_FALSE);
}

/* malloc */
sh_char_t*
SH_Boolean__to_s(SH_Boolean* obj) {
	sh_char_t* str = (sh_char_t*)malloc(sizeof(sh_char_t) * 3); /*FIXME*/
	str[0] = (sh_char_t)'?';
	str[1] = SH_Boolean__true(obj) ? (sh_char_t)'1' : (sh_char_t)'0';
	str[2] = (sh_char_t)0;
	return str;
}

/* vim: set ts=4 sts=4 sw=4: */
