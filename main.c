
#include <stdio.h>
#include <string.h>

#include "lib/types.h"
#include "lib/errors.h"
#include "lib/bareitem.h"
#include "lib/integer.h"
#include "lib/decimal.h"
#include "lib/string.h"
#include "lib/token.h"
#include "lib/bytesequence.h"
#include "lib/boolean.h"

void hexdump_string(const sh_char_t* str);

void do_sh_bareitem(SH_BareItem* obj);

void do_sh_null();

void do_sh_integer(sh_int_t value);
void do_sh_decimal(sh_float_t value);
void do_sh_string(sh_char_t* value, size_t n);
void do_sh_token(sh_char_t* value, size_t n);
void do_sh_bytesequence(sh_byte_t* value, size_t n);
void do_sh_boolean(sh_bool_t value);

int main() {

	sh_char_t unterminated_string[4] = {SH_CHAR_C('"'), SH_CHAR_C('\\'), SH_CHAR_C(0x20), SH_CHAR_C(0x7E)};
	sh_char_t unterminated_token[4] = {SH_CHAR_C('*'), SH_CHAR_C('#'), SH_CHAR_C(0x24), SH_CHAR_C(0x60)};
	sh_byte_t unterminated_bytes[6] = {SH_BYTE_C(0), SH_BYTE_C(1), SH_BYTE_C(0x7E), SH_BYTE_C(0x7F), SH_BYTE_C(0xFE), SH_BYTE_C(0xFF)};

	do_sh_null();

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

	printf("%c[32m === STRING ===============%c[0m\n", 0x1b, 0x1b);

	do_sh_string((sh_char_t*)"", 0);
	do_sh_string((sh_char_t*)"ABCxyz012!", 10);
	do_sh_string(unterminated_string, 4);

	printf("%c[32m === TOKEN ================%c[0m\n", 0x1b, 0x1b);

	do_sh_token((sh_char_t*)"", 0);
	do_sh_token((sh_char_t*)"foo123/456", 10);
	do_sh_token(unterminated_token, 4);

	printf("%c[32m === BYTE SEQUENCE ========%c[0m\n", 0x1b, 0x1b);

	do_sh_bytesequence((sh_byte_t*)"", 0);
	do_sh_bytesequence((sh_byte_t*)"ABCxyz\00012!", 10);
	do_sh_bytesequence(unterminated_bytes, 6);

	printf("%c[32m === BOOLEAN ==============%c[0m\n", 0x1b, 0x1b);

	do_sh_boolean(SH_TRUE);
	do_sh_boolean(SH_FALSE);
	do_sh_boolean(SH_BOOL_C(42));

	return 0;
}

void do_sh_bareitem(SH_BareItem* obj) {
	SH_Item_type t;
	sh_char_t* s;
	void* x;

	int err;

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

	int err;

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

	int err;

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
	SH_Decimal *obj;
	SH_BareItem *bi;

	sh_float_t f;
	sh_bool_t b;
	sh_int_t i;
	uint16_t u;
	sh_char_t* s;

	int err;

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
	SH_String *obj;
	SH_BareItem* bi;

	/* used to printf() value, looks like "%#{n}s" */
	char template[8];

	uint16_t u;
	sh_char_t* s;

	int err;

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
	SH_Token *obj;
	SH_BareItem* bi;

	/* used to printf() value, looks like "%#{n}s" */
	char template[8];

	sh_char_t* s;

	int err;

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
	SH_ByteSequence *obj;
	SH_BareItem* bi;

	uint16_t u;
	sh_char_t* s;

	int err;

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
	SH_Boolean *obj;
	SH_BareItem* bi;

	sh_bool_t b;
	sh_char_t* s;

	int err;

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

const char hexdump_rule[72] = "+--------------------------------------------------+-------------------+";
const char hexdump_line[72] = "|                                                  |                   |";
const char hexdump_char[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void hexdump_string(const sh_char_t* str) {
	sh_char_t* ptr = (sh_char_t*)str;
	int n = 0;
	int i, j;
	char line[72];

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
			memcpy((void*)line, (const void*)hexdump_line, sizeof(char)*72);
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
