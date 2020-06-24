#include "_hash.h"

#include <stdint.h>

uint8_t sh_hash8(const void* buf, size_t buflen) {
	uint8_t* ptr = (uint8_t*)buf;
	uint8_t hsh = UINT8_C(1);
	for (; buflen > 0; buflen--) {
		hsh = (hsh << 3) | (hsh >> 5);
		hsh ^= (uint8_t)*ptr;
		ptr++;
	}
	return hsh;
}

uint16_t sh_hash16(const void* buf, size_t buflen) {
	uint16_t* ptr = (uint16_t*)buf;
	uint16_t hsh = UINT16_C(1);
	for (; buflen > 1; buflen -= 2) {
		hsh = (hsh << 11) | (hsh >> 5);
		hsh ^= *ptr;
		ptr++;
	}
	if (buflen) {
		hsh = (hsh << 11) | (hsh >> 5);
		hsh ^= (uint16_t)*((uint8_t*)ptr);
	}
	return hsh;
}

/* vim: set ts=4 sts=4 sw=4: */
