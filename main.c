
#include <stdio.h>
#include <string.h>

#include "lib/_types.h"
#include "lib/_errors.h"
#include "lib/integer.h"
#include "lib/decimal.h"

void print_string(sh_char_t* str);

void do_sh_integer(sh_int_t value);
void dh_sh_decimal(sh_float_t value);

int main() {

	do_sh_integer(SH_INT_C(1));
	do_sh_integer(SH_INT_C(0));
	do_sh_integer(SH_INT_C(-1));
	do_sh_integer(SH_INT_C(12345));
	do_sh_integer(SH_INT_C(-12345));
	do_sh_integer(SH_INT_MAX);
	do_sh_integer(SH_INT_MIN);
	do_sh_integer(SH_INT_MAX+1);
	do_sh_integer(SH_INT_MIN-1);

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

	return 0;
}

void do_sh_integer(sh_int_t value) {
	SH_Integer* obj;

	sh_int_t i;
	sh_bool_t b;
	sh_char_t* s;

	obj = SH_Integer__init(value);
	if ((SH_Integer*)0 == obj) {
		printf("* unable to init SH_Integer(%lld)\n", (long long)value);
	} else {
		printf("+ init SH_Integer(%lld)\n", (long long)value);

		i = SH_Integer__int(obj);
		printf("  - int =: %lld\n", (long long)i);

		b = SH_Integer__negative(obj);
		printf("  - negative =: %hhu\n", (unsigned char)b);

		i = SH_Integer__abs(obj);
		printf("  - abs =: %lld\n", (long long)i);

		s = SH_Integer__to_s(obj);
		if ((sh_char_t*)0 == s) {
			printf("  * unable to to_s\n");
		} else {
			printf("  - to_s =:\n");
			print_string(s);
			free(s);
		}

		SH_Integer__destroy(obj);
	}
	printf("\n");
}

void do_sh_decimal(sh_float_t value) {
	SH_Decimal *obj;

	sh_float_t f;
	sh_bool_t b;
	sh_int_t i;
	uint16_t u;
	sh_char_t* s;

	obj = SH_Decimal__init(value);
	if ((SH_Decimal*)0 == obj) {
		printf("* unable to init SH_Decimal(%.4F)\n", (double)value);
	} else {
		printf("+ init SH_Decimal(%.4F)\n", (double)value);

		f = SH_Decimal__float(obj);
		printf("  - float =: %.4F\n", (double)f);

		f = SH_Decimal__abs(obj);
		printf("  - abs =: %.4F\n", (double)f);

		b = SH_Decimal__negative(obj);
		printf("  - negative =: %hhu\n", (unsigned char)b);

		i = SH_Decimal__integer_part(obj);
		printf("  - integer_part =: %lld\n", (long long)i);

		u = SH_Decimal__fractional_part(obj);
		printf("  - fractional_part =: %hu\n", u);

		s = SH_Decimal__to_s(obj);
		if ((sh_char_t*)0 == s) {
			printf("  * unable to to_s\n");
		} else {
			printf("  - to_s =:\n");
			print_string(s);
			free(s);
		}

		SH_Decimal__destroy(obj);
	}
	printf("\n");
}

const char hexdump_rule[72] = "+--------------------------------------------------+-------------------+";
const char hexdump_line[72] = "|                                                  |                   |";
const char hexdump_char[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void print_string(sh_char_t* str) {
	sh_char_t* ptr = str;
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

		if (*ptr > SH_CHAR_C(0x20) && *ptr < SH_CHAR_C(0x7F)) {
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

