#ifndef DICT_H
#define DICT_H

#include <stdlib.h>
#include "tstring.h"

typedef struct {
    int *keys;
    tstring *values;
    int len;
    int allocated;
} dict;

void allocate_dict(dict *in, int n); /*Allocates dict*/

void double_size_dict(dict *in); /*Doubles dict size*/

/*void tidy_dict(dict *in); Unused*/

void push_dict_key(dict *in, int key); /*Adds key to dict*/

void append_char_all(dict *in, char c); /*Appends char to all values of dict*/

void merge_dict(dict *in1, dict *in2); /*adds keys and values of in2 to in1 and frees unused keys in in1 and in2*/

/*tstring *get_value(dict *in, int n); Legace - replaced by hashmap*/

void free_dict(dict *in); /*frees dict*/

#endif
