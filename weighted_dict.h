#ifndef WEIGHTED_DICT_H
#define WEIGHTED_DICT_H

#include <stdlib.h>
#include "dict.h"

typedef struct {
    int *weights;
    dict *dicts;
    int len;
    int allocated;
} weighted_dict;

void allocate_weighted_dict(weighted_dict *in, int n);

void double_weighted_dict(weighted_dict *in);

void push_weighted_dict(weighted_dict *in, int key);

void add_count(weighted_dict *in, int key);

void move_value(weighted_dict *in, int start);

void merge_on_start(weighted_dict *in, int start);

void sort_weighted_dict(weighted_dict *in);

void free_weighted_dict(weighted_dict *in);
#endif
