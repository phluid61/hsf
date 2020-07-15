#ifndef _SH_DICT_H_
#define _SH_DICT_H_

#include "types.h"

#include <stdint.h>

/* 8-bit hash = 256 buckets */
#define SH_dict_bucket_count 256

/* For a perfect hash, 1024 pairs / 256 buckets = 4 pairs per bucket */
#define SH_dict_bucket_size 4

typedef struct SH_dict_pair SH_dict_pair;
struct SH_dict_pair {
	SH_Key* key;
	SH_Item* value;
};

typedef struct SH_dict_bucket SH_dict_bucket;
struct SH_dict_bucket {
	size_t num;
	SH_dict_pair* pairs[SH_dict_bucket_size];
	SH_dict_bucket* next; /* in case there are more than SH_dict_bucket_size keys with the same hash */
};

typedef struct SH_dict SH_dict;
struct SH_dict {
	/* array using hash for index */
	SH_dict_bucket* _hash[SH_dict_bucket_count];

	/* insertion-ordered linked list */
	SH_dict_bucket* _list;
};

SH_dict_pair*
SH_dict_pair__init(SH_Key* key, SH_Item* value, int* err);

SH_dict_bucket*
SH_dict_bucket__init(int* err);

void
SH_dict_bucket__add(SH_dict_bucket* obj, SH_dict_pair* pair, int* err);

SH_dict*
SH_dict__init(int* err);

SH_dict_pair*
SH_dict__get(SH_dict* obj, SH_Key* key, int* err);

void
SH_dict__add(SH_dict* obj, SH_dict_pair* pair, int* err);

#endif
