#include "dict.h"
#include "tstring.h"
#include <stdlib.h>

/* Checked, no shown errors, correct output, valgrind is angry, don't know why'*/

void allocate_dict(dict *in, int n) {
    int i;
    in->keys = calloc(n, sizeof(int));
    in->values = calloc(n, sizeof(tstring));
    for(i=0; i<n; i++)
        allocate_str(&in->values[i], 100);
    in->allocated = n;
}

void double_size_dict(dict *in) {
    int i;
    in->allocated *= 2;
    in->keys = realloc(in->keys, sizeof(int) * in->allocated);
    in->values = realloc(in->values, sizeof(tstring) * in->allocated);
    for(i=in->len; i<in->allocated; i++)
        allocate_str(&in->values[i], 1);
}

/*void tidy_dict(dict *in) { Unused
    int i;
    for(i=0; i<in->len; i++)
        tidy_str(&in->values[i]);
}*/

void push_dict_key(dict *in, int key) {
    if(in->len == in->allocated)
        double_size_dict(in);
    in->keys[in->len] = key;
    /*allocate_str(&in->values[in->len], 1); Legacy-allocated on initialization*/
    in->len++;
}

void append_char_all(dict *in, char c) {
    int i;
    for(i=0; i<in->len; i++)
        push_str(&in->values[i], c);
}

void merge_dict(dict *in1, dict *in2) {
    int i;
    for(i=0; i<in2->len; i++) {
        push_dict_key(in1, in2->keys[i]);
        free_str(&in1->values[in1->len-1]);
        in1->values[in1->len-1] = in2->values[i];
    }
    free(in2->keys);
    for(i=in2->len; i<in2->allocated; i++)
        free_str(&in2->values[i]);
    free(in2->values);
}

/*tstring *get_value(dict *in, int n) { Legacy -replaced by "hashtable"
    int i;
    for(i=0; i<in->len; i++)
        if(in->keys[i]==n)
            return &in->values[i];
    return NULL;
}*/

void free_dict(dict *in) {
    int i;
    for(i=0; i<in->allocated; i++)
        free_str(&in->values[i]);
    free(in->values);
    free(in->keys);
}
