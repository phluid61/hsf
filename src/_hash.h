#ifndef _SH_HASH_H_
#define _SH_HASH_H_

#include <stdint.h>

uint16_t sh_hash8(const void* buf, size_t buflen);
uint16_t sh_hash16(const void* buf, size_t buflen);

#ifndef
/* vim: set ts=4 sts=4 sw=4: */
