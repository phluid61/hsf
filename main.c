
#include <stdio.h>
#include <string.h>

#include "lib/types.h"
#include "lib/errors.h"
#include "lib/_dict.h"
#include "lib/key.h"
#include "lib/item.h"
#include "lib/bareitem.h"
#include "lib/integer.h"
#include "lib/decimal.h"
#include "lib/string.h"
#include "lib/token.h"
#include "lib/bytesequence.h"
#include "lib/boolean.h"
#include "lib/list.h"

void hexdump_string(const sh_char_t* str);

void do_sh_bareitem(SH_BareItem* obj);

void do_sh_null();

void do_sh_integer(sh_int_t value);
void do_sh_decimal(sh_float_t value);
void do_sh_string(sh_char_t* value, size_t n);
void do_sh_token(sh_char_t* value, size_t n);
void do_sh_bytesequence(sh_byte_t* value, size_t n);
void do_sh_boolean(sh_bool_t value);
void do_sh_item();
void do_sh_list();

int main() {

	#ifndef NO_STRING
	sh_char_t unterminated_string[4] = {SH_CHAR_C('"'), SH_CHAR_C('\\'), SH_CHAR_C(0x20), SH_CHAR_C(0x7E)};
	#endif
	#ifndef NO_TOKEN
	sh_char_t unterminated_token[4] = {SH_CHAR_C('*'), SH_CHAR_C('#'), SH_CHAR_C(0x24), SH_CHAR_C(0x60)};
	#endif
	#ifndef NO_BYTESEQ
	sh_byte_t unterminated_bytes[6] = {SH_BYTE_C(0), SH_BYTE_C(1), SH_BYTE_C(0x7E), SH_BYTE_C(0x7F), SH_BYTE_C(0xFE), SH_BYTE_C(0xFF)};
	#endif

	#ifndef NO_NULL
	do_sh_null();
	#endif

	#ifndef NO_INTEGER
	printf("%c[32m === INTEGER ==============%c[0m\n", 0x1b, 0x1b);

	do_sh_integer(SH_INT_C(1));
	do_sh_integer(SH_INT_C(0));
	do_sh_integer(SH_INT_C(-1));
	do_sh_integer(SH_INT_C(12345));
	do_sh_integer(SH_INT_C(-12345));
	do_sh_integer(SH_INT_MAX);
	do_sh_integer(SH_INT_MIN);
	do_sh_integer(SH_INT_MAX+1);
	do_sh_integer(SH_INT_MIN-1);
	#endif

	#ifndef NO_DECIMAL
	printf("%c[32m === DECIMAL ==============%c[0m\n", 0x1b, 0x1b);

	do_sh_decimal(SH_FLOAT_C(1.0));
	do_sh_decimal(SH_FLOAT_C(0.0));
	do_sh_decimal(SH_FLOAT_C(-1.0));
	do_sh_decimal(SH_FLOAT_C(123456789012.123));
	do_sh_decimal(SH_FLOAT_C(-123456789012.123));
	do_sh_decimal(SH_FLOAT_C(3.14159265359));
	do_sh_decimal(SH_FLOAT_C(-3.14159265359));
	do_sh_decimal(SH_FLOAT_C(123456789012.1234));
	do_sh_decimal(SH_FLOAT_C(-123456789012.1234));
	do_sh_decimal(SH_FLOAT_C(1000000000000.0));
	do_sh_decimal(SH_FLOAT_C(-1000000000000.0));
	#endif

	#ifndef NO_STRING
	printf("%c[32m === STRING ===============%c[0m\n", 0x1b, 0x1b);

	do_sh_string((sh_char_t*)"", 0);
	do_sh_string((sh_char_t*)"ABCxyz012!", 10);
	do_sh_string(unterminated_string, 4);
	#endif

	#ifndef NO_TOKEN
	printf("%c[32m === TOKEN ================%c[0m\n", 0x1b, 0x1b);

	do_sh_token((sh_char_t*)"", 0);
	do_sh_token((sh_char_t*)"foo123/456", 10);
	do_sh_token(unterminated_token, 4);
	#endif

	#ifndef NO_BYTESEQ
	printf("%c[32m === BYTE SEQUENCE ========%c[0m\n", 0x1b, 0x1b);

	do_sh_bytesequence((sh_byte_t*)"", 0);
	do_sh_bytesequence((sh_byte_t*)"ABCxyz\00012!", 10);
	do_sh_bytesequence(unterminated_bytes, 6);
	#endif

	#ifndef NO_BOOLEAN
	printf("%c[32m === BOOLEAN ==============%c[0m\n", 0x1b, 0x1b);

	do_sh_boolean(SH_TRUE);
	do_sh_boolean(SH_FALSE);
	do_sh_boolean(SH_BOOL_C(42));
	#endif

	#ifndef NO_PARAMETERS
	printf("%c[32m === PARAMETERS ===========%c[0m\n", 0x1b, 0x1b);

	do_sh_item();
	#endif

	#ifndef NO_LIST
	printf("%c[32m === LIST =================%c[0m\n", 0x1b, 0x1b);

	do_sh_list();
	#endif

	return 0;
}

void do_sh_bareitem(SH_BareItem* obj) {
	SH_Item_type t;
	sh_char_t* s;
	void* x;

	int err = 0;

	t = SH_BareItem__type(obj, 0);
	printf("    - type =: %u\n", (unsigned int)t);

	x = (void*)SH_BareItem__get_integer(obj, &err);
	printf("    o get_integer: [%llX] 0x%08X\n", (long long)x, err);

	x = (void*)SH_BareItem__get_decimal(obj, &err);
	printf("    o get_decimal: [%llX] 0x%08X\n", (long long)x, err);

	x = (void*)SH_BareItem__get_string(obj, &err);
	printf("    o get_string: [%llX] 0x%08X\n", (long long)x, err);

	x = (void*)SH_BareItem__get_token(obj, &err);
	printf("    o get_token: [%llX] 0x%08X\n", (long long)x, err);

	x = (void*)SH_BareItem__get_bytesequence(obj, &err);
	printf("    o get_bytesequence: [%llX] 0x%08X\n", (long long)x, err);

	x = (void*)SH_BareItem__get_boolean(obj, &err);
	printf("    o get_boolean: [%llX] 0x%08X\n", (long long)x, err);

	s = SH_BareItem__to_s(obj, &err);
	if ((sh_char_t*)0 == s || err) {
		printf("    * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
	} else {
		printf("    - to_s =:\n");
		hexdump_string(s);
		free(s);
	}
}

void do_sh_null() {
	SH_BareItem* bi;

	int err = 0;

	printf("+ NULL item\n");

	bi = SH_BareItem__init_null(&err);
	if ((SH_BareItem*)0 == bi || err) {
		printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
	} else {
		printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
		do_sh_bareitem(bi);
		SH_BareItem__destroy(bi, SH_FALSE, 0);
	}
}

void do_sh_integer(sh_int_t value) {
	SH_Integer* obj;
	SH_BareItem* bi;

	sh_int_t i;
	sh_bool_t b;
	sh_char_t* s;

	int err = 0;

	obj = SH_Integer__init(value, &err);
	if ((SH_Integer*)0 == obj || err) {
		printf("* unable to init SH_Integer(%lld): [%llX] 0x%08X\n", (long long)value, (long long)obj, err);
	} else {
		printf("+ init SH_Integer(%lld): [%llX]\n", (long long)value, (long long)obj);

		i = SH_Integer__int(obj, 0);
		printf("  - int =: %lld\n", (long long)i);

		b = SH_Integer__negative(obj, 0);
		printf("  - negative =: %hhu\n", (unsigned char)b);

		i = SH_Integer__abs(obj, 0);
		printf("  - abs =: %lld\n", (long long)i);

		s = SH_Integer__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_integer(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_Integer__destroy(obj, 0);
	}
}

void do_sh_decimal(sh_float_t value) {
	SH_Decimal* obj;
	SH_BareItem* bi;

	sh_float_t f;
	sh_bool_t b;
	sh_int_t i;
	uint16_t u;
	sh_char_t* s;

	int err = 0;

	obj = SH_Decimal__init(value, &err);
	if ((SH_Decimal*)0 == obj || err) {
		printf("* unable to init SH_Decimal(%.4F): [%llX] 0x%08X\n", (double)value, (long long)obj, err);
	} else {
		printf("+ init SH_Decimal(%.4F): [%llX]\n", (double)value, (long long)obj);

		f = SH_Decimal__float(obj, 0);
		printf("  - float =: %.4F\n", (double)f);

		f = SH_Decimal__abs(obj, 0);
		printf("  - abs =: %.4F\n", (double)f);

		b = SH_Decimal__negative(obj, 0);
		printf("  - negative =: %hhu\n", (unsigned char)b);

		i = SH_Decimal__integer_part(obj, 0);
		printf("  - integer_part =: %lld\n", (long long)i);

		u = SH_Decimal__fractional_part(obj, 0);
		printf("  - fractional_part =: %hu\n", u);

		s = SH_Decimal__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_decimal(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_Decimal__destroy(obj, 0);
	}
}

void do_sh_string(sh_char_t* value, size_t n) {
	SH_String* obj;
	SH_BareItem* bi;

	/* used to printf() value, looks like "%#{n}s" */
	char template[8];

	uint16_t u;
	sh_char_t* s;

	int err = 0;

	snprintf(template, 8, "%%%lus", n);

	obj = SH_String__init(value, n, &err);
	if ((SH_String*)0 == obj || err) {
		printf("* unable to init SH_String(\"");
		printf(template, (char*)value);
		printf("\", %lu): [%llX] 0x%08X\n", n, (long long)obj, err);
	} else {
		printf("+ init SH_String(\"");
		printf(template, (char*)value);
		printf("\", %lu): [%llX]\n", n, (long long)obj);

		u = SH_String__length(obj, 0);
		printf("  - length =: %hu\n", u);

		s = SH_String__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_string(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_String__destroy(obj, 0);
	}
}

void do_sh_token(sh_char_t* value, size_t n) {
	SH_Token* obj;
	SH_BareItem* bi;

	/* used to printf() value, looks like "%#{n}s" */
	char template[8];

	sh_char_t* s;

	int err = 0;

	snprintf(template, 8, "%%%lus", n);

	obj = SH_Token__init(value, n, &err);
	if ((SH_Token*)0 == obj || err) {
		printf("* unable to init SH_Token(\"");
		printf(template, (char*)value);
		printf("\", %lu): [%llX] 0x%08X\n", n, (long long)obj, err);
	} else {
		printf("+ init SH_Token(\"");
		printf(template, (char*)value);
		printf("\", %lu): [%llX]\n", n, (long long)obj);

		s = SH_Token__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_token(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_Token__destroy(obj, 0);
	}
}

void do_sh_bytesequence(sh_byte_t* value, size_t n) {
	SH_ByteSequence* obj;
	SH_BareItem* bi;

	uint16_t u;
	sh_char_t* s;

	int err = 0;

	obj = SH_ByteSequence__init(value, n, &err);
	if ((SH_ByteSequence*)0 == obj || err) {
		printf("* unable to init SH_ByteSequence({...");
		printf("}, %lu): [%llX] 0x%08X\n", n, (long long)obj, err);
	} else {
		printf("+ init SH_ByteSequence({...");
		printf("}, %lu): [%llX]\n", n, (long long)obj);

		u = SH_ByteSequence__length(obj, 0);
		printf("  - length =: %hu\n", u);

		s = SH_ByteSequence__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_bytesequence(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_ByteSequence__destroy(obj, 0);
	}
}

void do_sh_boolean(sh_bool_t value) {
	SH_Boolean* obj;
	SH_BareItem* bi;

	sh_bool_t b;
	sh_char_t* s;

	int err = 0;

	obj = SH_Boolean__init(value, &err);
	if ((SH_Boolean*)0 == obj || err) {
		printf("* unable to init SH_Boolean(%hhu): [%llX] 0x%08X\n", (unsigned char)value, (long long)obj, err);
	} else {
		printf("+ init SH_Boolean(%hhu): [%llX]\n", (unsigned char)value, (long long)obj);

		b = SH_Boolean__bool(obj, 0);
		printf("  - bool =: %hhu\n", b);

		b = SH_Boolean__true(obj, 0);
		printf("  - true =: %hhu\n", b);

		b = SH_Boolean__false(obj, 0);
		printf("  - false =: %hhu\n", b);

		s = SH_Boolean__to_s(obj, &err);
		if ((sh_char_t*)0 == s || err) {
			printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
		} else {
			printf("  - to_s =:\n");
			hexdump_string(s);
			free(s);
		}

		bi = SH_BareItem__init_boolean(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);
			do_sh_bareitem(bi);
			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_Boolean__destroy(obj, 0);
	}
}

/***** everything from here down is experimental *****/

void __display_item(SH_Item* obj) {
	int err = 0;
	sh_char_t* s;

	s = SH_Item__to_s(obj, &err);
	if ((sh_char_t*)0 == s) {
		printf("<<ERR:%08x>>\n", err);
	} else {
		printf("%s\n", s);
		free(s);
	}
}
void __do_sh_item(SH_Item* obj) {
	int err = 0;

	SH_Key  *key1, *key2, *key3;
	SH_Item *val1, *val2, *val3;

	__display_item(obj);

	key1 = SH_Key__init((unsigned char*)"key1", 4, &err);
	val1 = SH_Item__init(SH_BareItem__init_boolean(SH_Boolean__init(SH_TRUE, &err), &err), 0, &err);

	SH_Item__add_param(obj, key1, val1, &err);
	__display_item(obj);

	key2 = SH_Key__init((unsigned char*)"k2", 2, &err);
	val2 = SH_Item__init(SH_BareItem__init_boolean(SH_Boolean__init(SH_FALSE, &err), &err), 0, &err);

	SH_Item__add_param(obj, key2, val2, &err);
	__display_item(obj);

	key3 = SH_Key__init((unsigned char*)"three", 5, &err);
	val3 = SH_Item__init(SH_BareItem__init_integer(SH_Integer__init(1234, &err), &err), 0, &err);

	SH_Item__add_param(obj, key3, val3, &err);
	__display_item(obj);
}

void do_sh_item() {
	sh_char_t value[4] = "foo";

	SH_Token* obj;
	SH_BareItem* bi;
	SH_Item* item;

	SH_dict* params;

	SH_Key  *key1;
	SH_Item *val1;

	int err = 0;

	obj = SH_Token__init(value, 3, &err);
	if ((SH_Token*)0 == obj || err) {
		printf("* unable to init SH_Token(%s): [%llX] 0x%08X\n", (char*)value, (long long)obj, err);
	} else {
		printf("+ init SH_Token(%s): [%llX]\n", (char*)value, (long long)obj);
		bi = SH_BareItem__init_token(obj, &err);
		if ((SH_BareItem*)0 == bi || err) {
			printf("  * unable to init SH_BareItem: [%llX] 0x%08X\n", (long long)bi, err);
		} else {
			printf("  + init SH_BareItem: [%llX]\n", (long long)bi);

			printf("  %c[36m--- create an item without any parameters -----%c[0m\n", 0x1b, 0x1b);
			item = SH_Item__init(bi, (SH_dict*)0, &err);
			if ((SH_Item*)0 == item || err) {
				printf("    * unable to init SH_Item: [%llX] 0x%08X\n", (long long)item, err);
			} else {
				printf("    + init SH_Item: [%llX]\n", (long long)item);
				__do_sh_item(item);

				SH_Item__destroy(item, SH_FALSE, 0);
			}

			printf("  %c[36m--- create an item with explicit parameters ---%c[0m\n", 0x1b, 0x1b);
			params = SH_dict__init(&err);
			if ((SH_dict*)0 == params || err) {
				printf("    * unable to init SH_dict: [%llX] 0x%08X\n", (long long)params, err);
			} else {
				printf("    + init SH_dict: [%llX]\n", (long long)params);

				item = SH_Item__init(bi, params, &err);
				if ((SH_Item*)0 == item || err) {
					printf("      * unable to init SH_Item: [%llX] 0x%08X\n", (long long)item, err);
				} else {
					printf("      + init SH_Item: [%llX]\n", (long long)item);
					__do_sh_item(item);

					SH_Item__destroy(item, SH_FALSE, 0);
				}

				SH_dict__destroy(params, SH_TRUE, 0);
			}

			printf("  %c[36m--- create an item with defined parameters ----%c[0m\n", 0x1b, 0x1b);
			params = SH_dict__init(&err);
			if ((SH_dict*)0 == params || err) {
				printf("    * unable to init SH_dict: [%llX] 0x%08X\n", (long long)params, err);
			} else {
				printf("    + init SH_dict: [%llX]\n", (long long)params);

				/* FIXME: catch errors here: */
				key1 = SH_Key__init((unsigned char*)"test", 4, &err);
				val1 = SH_Item__init(SH_BareItem__init_integer(SH_Integer__init(SH_INT_C(42), &err), &err), 0, &err);
				if (err) {
					printf("      x [%llX]=[%llX] 0x%08X\n", (long long)key1, (long long)val1, err);
				}
				SH_dict__add(params, key1, val1, &err);

				item = SH_Item__init(bi, params, &err);
				if ((SH_Item*)0 == item || err) {
					printf("      * unable to init SH_Item: [%llX] 0x%08X\n", (long long)item, err);
				} else {
					printf("      + init SH_Item: [%llX]\n", (long long)item);
					__do_sh_item(item);

					SH_Item__destroy(item, SH_FALSE, 0);
				}

				SH_dict__destroy(params, SH_TRUE, 0);
			}

			SH_BareItem__destroy(bi, SH_FALSE, 0);
		}

		SH_Token__destroy(obj, 0);
	}
}

void _print_list(SH_List* list) {
	sh_char_t* s;
	int err = 0;

	printf("  - count = %lu\n", list->count);

	s = SH_List__to_s(list, &err);
	if ((sh_char_t*)0 == s || err) {
		printf("  * unable to to_s: [%llX] 0x%08X\n", (long long)s, err);
	} else {
		printf("  - to_s =:\n");
		hexdump_string(s);
		free(s);
	}
}
void do_sh_list() {
	SH_List* list;

	SH_Boolean* obj;
	SH_BareItem* bi;
	SH_Item* item;

	int err = 0;

	list = SH_List__init(&err);
	if ((SH_List*)0 == list || err) {
		printf("* unable to init SH_List: [%llX] 0x%08X\n", (long long)list, err);
	} else {
		printf("+ init SH_List: [%llX]\n", (long long)list);

		_print_list(list);

		obj = SH_Boolean__init(SH_FALSE, &err);
		if ((SH_Boolean*)0 == obj || err) {
			/**/
		} else {
			bi = SH_BareItem__init_boolean(obj, &err);
			if ((SH_BareItem*)0 == bi || err) {
				/**/
			} else {
				item = SH_Item__init(bi, (SH_dict*)0, &err);
				if ((SH_Item*)0 == item || err) {
					/**/
				} else {
					SH_List__add(list, item, &err);
					if (err) {
						printf("  * unable to add: 0x%08X\n", err);
					} else {
						_print_list(list);
					}

					SH_List__add(list, item, &err);
					if (err) {
						printf("  * unable to add: 0x%08X\n", err);
					} else {
						_print_list(list);
					}

					SH_List__add(list, item, &err);
					if (err) {
						printf("  * unable to add: 0x%08X\n", err);
					} else {
						_print_list(list);
					}

					SH_Item__destroy(item, SH_FALSE, 0);
				}
				SH_BareItem__destroy(bi, SH_FALSE, 0);
			}
			SH_Boolean__destroy(obj, 0);
		}
		SH_List__destroy(list, SH_FALSE, 0);
	}
}

/***** everything from here up is experimental *****/

const char hexdump_rule[73] = "+--------------------------------------------------+-------------------+";
const char hexdump_line[73] = "|                                                  |                   |";
const char hexdump_char[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void hexdump_string(const sh_char_t* str) {
	sh_char_t* ptr = (sh_char_t*)str;
	int n = 0;
	int i, j;
	char line[73];

	if ((sh_char_t*)0 == ptr) {
		printf("NULL\n");
		return;
	}
	if (SH_CHAR_C(0) == *ptr) {
		printf("\"\"\n");
		return;
	}

	printf("%s\n", hexdump_rule);

	while (SH_CHAR_C(0) != *ptr) {
		if (n == 0) {
			memcpy((void*)line, (const void*)hexdump_line, sizeof(char)*73);
			i = 2;
			j = 53;
		}
		if (n == 8) {
			i++;
			j++;
		}

		line[i++] = hexdump_char[((*ptr) & 0xF0) >> 4];
		line[i++] = hexdump_char[ (*ptr) & 0x0F];
		i++;

		if (*ptr >= SH_CHAR_C(0x20) && *ptr < SH_CHAR_C(0x7F)) {
			line[j++] = (char)(*ptr);
		} else {
			line[j++] = '.';
		}

		ptr++;
		n++;
		if (n == 16) {
			printf("%s\n", line);
			n = 0;
		}
	}

	if (n != 0) {
		printf("%s\n", line);
	}

	printf("%s\n", hexdump_rule);
}

/* vim: set ts=4 sts=4 sw=4: */
