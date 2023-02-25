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

void allocate_dict(dict *in, int n);

void double_size_dict(dict *in);

void tidy_dict(dict *in);

void push_dict_key(dict *in, int key);

void append_char_all(dict *in, char c);

void merge(dict *in1, dict *in2);

void free_dict(dict *in);
#endif
