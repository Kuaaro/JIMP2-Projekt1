#include <stdlib.h>
#include "weighted_dict.h"
#include "dict.h"
#include "tstring.h"

void allocate_and_fill_weighted_dict(weighted_dict *in, int n) { /*Allocates and fills weighted_dict with default values*/
    int i;
    in->weights = calloc(n, sizeof(int));
    in->dicts = calloc(n, sizeof(dict));
    in->allocated = n;
    in->len = n;
    for(i=0; i<n; i++) {
        allocate_dict(&in->dicts[i], 1);
        push_dict_key(&in->dicts[i], i);
    }
}

/* legacy
void double_weighted_dict(weighted_dict *in) {
    int i;
    in->allocated *= 2;
    in->weights = realloc(in->weights, sizeof(int) * in->allocated);
    in->dicts = realloc(in->dicts, sizeof(dict) * in->allocated);
    for(i=in->len; i<in->allocated; i++)
        allocate_dict(&in->dicts[i], 1);
}

legacy
void push_weighted_dict(weighted_dict *in, int key) {
    if(in->len == in->allocated)
        double_weighted_dict(in);
    in->weights[in->len] = 1;
    allocate_dict(&in->dicts[in->len], 1);
    push_dict_key(&in->dicts[in->len], key);
    in->len++;
}

legacy
void add_count(weighted_dict *in, int key) {
    int i;
    for(i=0; i<in->len; i++)
        if(in->dicts[i].keys[0] == key) {
            in->weights[i]++;
            break;
        }
    if(i==in->len)
        push_weighted_dict(in, key);
}

legacy
void fill_weighted_dict(weighted_dict *in) {
    int i;
    for(i=0; i<in->allocated; i++)
        push_dict_key(&in->dicts[i], i);
    in->len = in->allocated;
}*/

void add_count(weighted_dict *in, int key) { /*nice wrap to adding one count*/
    in->weights[key]++;
}

void move_value(weighted_dict *in, int start) { /*Sorts in value after change*/
    int i;
    /*free(in->dicts[start + 1].keys);*/
    for(i=start + 2; i<in->len; i++) {
        if(in->weights[start] > in->weights[i]) {
            in->weights[i-1] = in->weights[i];
            in->dicts[i-1] = in->dicts[i];
        } else
            break;
    }
    in->weights[i-1] = in->weights[start];
    in->dicts[i-1] = in->dicts[start];
}

void merge_weighted_dict_on_start(weighted_dict *in, int start) { /*merges dict[start+1] to dict[start]*/
    in->weights[start] += in->weights[start+1];
    merge_dict(&in->dicts[start], &in->dicts[start+1]);
}

void sort_weighted_dict(weighted_dict *in) { /*Sorts weighted dict by weights*/
    int i, temp_i, ct = 1;
    dict temp_d;
    while(ct) {
        ct = 0;
        for(i=1; i<in->len; i++)
            if(in->weights[i-1] > in->weights[i]) {

                temp_i = in->weights[i];
                in->weights[i] = in->weights[i-1];
                in->weights[i-1] = temp_i;

                temp_d = in->dicts[i];
                in->dicts[i] = in->dicts[i-1];
                in->dicts[i-1] = temp_d;

                ct++;
            }
    }
}

/*void free_weighted_dict(weighted_dict *in) { unused
    int i;
    free(in->weights);
    for(i=0; i<in->len; i++)
        free_dict(&in->dicts[i]);
    free(in->dicts);
}*/
