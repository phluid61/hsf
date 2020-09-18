#include "_dict.h"

#include "types.h"
#include "errors.h"
#include "key.h"
#include "item.h"

#include <stdint.h>

#define __clear(v)      { if ((int*)0 != (v)) *(v) = SH_E_NO_ERROR; }
#define __raise(v,code) { if ((int*)0 != (v)) *(v) = (code); }

SH_dict_pair*
SH_dict_pair__init(SH_Key* key, SH_Item* value, int* err) {
	SH_dict_pair* obj;

	obj = (SH_dict_pair*)malloc(sizeof(SH_dict_pair));
	if ((SH_dict_pair*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_dict_pair*)0;
	}

	obj->key = key;
	obj->value = value;

	__clear(err);
	return obj;
}

void
SH_dict_pair__destroy(SH_dict_pair* obj, sh_bool_t recursive, int* err) {
	if (recursive) {
		SH_Key__destroy(obj->key, err);
		SH_Item__destroy(obj->value, recursive, err);
	}
	free(obj);
	__clear(err);
}

SH_dict_bucket*
SH_dict_bucket__init(int *err) {
	SH_dict_bucket* obj;

	obj = (SH_dict_bucket*)calloc(sizeof(SH_dict_bucket), 1);
	if ((SH_dict_bucket*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_dict_bucket*)0;
	}

	__clear(err);
	return obj;
}

void
SH_dict_bucket__destroy(SH_dict_bucket* obj, sh_bool_t recursive, int* err) {
	if ((SH_dict_bucket*)0 != obj->next) {
		SH_dict_bucket__destroy(obj->next, recursive, err);
	}
	while (obj->num > (size_t)0) {
		obj->num --;
		SH_dict_pair__destroy(obj->pairs[obj->num], recursive, err);
	}
	free(obj);
	__clear(err);
}

void
SH_dict_bucket__add(SH_dict_bucket* obj, SH_dict_pair* pair, int* err) {
	while (obj->num >= SH_dict_bucket_size) {
		if ((SH_dict_bucket*)0 == obj->next) {
			obj->next = SH_dict_bucket__init(err);
			if (err) return;
		}
		obj = obj->next;
	}
	obj->pairs[obj->num] = pair;
	obj->num ++;

	__clear(err);
}

SH_dict*
SH_dict__init(int* err) {
	SH_dict* obj;

	obj = (SH_dict*)calloc(sizeof(SH_dict), 1);
	if ((SH_dict*)0 == obj) {
		__raise(err, SH_E_MALLOC_ERROR);
		return (SH_dict*)0;
	}

	__clear(err);
	return obj;
}

void
SH_dict__destroy(SH_dict* obj, sh_bool_t recursive, int* err) {
	if ((SH_dict_bucket*)0 != obj->_list) {
		SH_dict_bucket__destroy(obj->_list, recursive, err);
	}
	free(obj);
	__clear(err);
}

SH_dict_pair*
SH_dict__get(SH_dict* obj, SH_Key* key, int* err) {
	size_t i;
	uint8_t hash;
	SH_dict_bucket* bucket;
	SH_dict_pair* pair;

	hash = SH_Key__hash(key, err);
	bucket = obj->_hash[hash];

	while ((SH_dict_bucket*)0 != bucket) {
		for (i = 0; /*i < SH_dict_bucket_size &&*/ i < bucket->num; i++) {
			pair = bucket->pairs[i];
			if (SH_Key__equal(key, pair->key, 0)) { /*FIXME: err?*/
				__clear(err);
				return pair;
			}
		}
		bucket = bucket->next;
	}

	/* not found, but no error */
	__clear(err);
	return (SH_dict_pair*)0;
}

/* doesn't check for duplicates */
void
SH_dict__add(SH_dict* obj, SH_Key* key, SH_Item* value, int* err) {
	SH_dict_pair* pair;
	uint8_t hash;

	pair = SH_dict_pair__init(key, value, err);
	if (err) return;

	/* add it to the _hash array */

	hash = SH_Key__hash(pair->key, err);
	if ((SH_dict_bucket*)0 == obj->_hash[hash]) {
		obj->_hash[hash] = SH_dict_bucket__init(err);
		if (err) return;
	}
	SH_dict_bucket__add(obj->_hash[hash], pair, err);
	if (err) return;

	/* add it to the _list list */

	if ((SH_dict_bucket*)0 == obj->_list) {
		obj->_list = SH_dict_bucket__init(err);
		if (err) return;
	}
	SH_dict_bucket__add(obj->_list, pair, err);
	if (err) return; /* FIXME are we left in a broken state? */
}

/* vim: set ts=4 sts=4 sw=4: */
