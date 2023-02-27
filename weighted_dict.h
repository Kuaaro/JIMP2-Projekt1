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

void allocate_and_fill_weighted_dict(weighted_dict *in, int n); /*Allocates and fills weighted_dict with default values*/

/*
legacy

void double_weighted_dict(weighted_dict *in);

void push_weighted_dict(weighted_dict *in, int key);

void fill_weighted_dict(weighted_dict *in); unused
*/
void add_count(weighted_dict *in, int key); /*nice wrap to adding one count*/

void move_value(weighted_dict *in, int start); /*Sorts in value after change*/

void merge_weighted_dict_on_start(weighted_dict *in, int start); /*merges dict[start+1] to dict[start]*/

void sort_weighted_dict(weighted_dict *in); /*Sorts weighted dict by weights*/

/*void free_weighted_dict(weighted_dict *in); unused*/
#endif
