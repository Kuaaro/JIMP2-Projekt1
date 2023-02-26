#include "tstring.h"
#include <stdlib.h>

/*All checked - no leaks*/

void allocate_str(tstring *in, int n) {
    in->text = calloc(n, sizeof(char));
    in->allocated = n;
}

void double_size_str(tstring *in) {
    in->allocated *= 2;
    in->text = realloc(in->text, sizeof(char) * in->allocated); /*Check if pointer*/
}

/*void tidy_str(tstring *in) { Unused
    int i;
    for(i=in->len; i<in->allocated; i++)
        in->text[i] = 0;
}*/

void push_str(tstring *in, char a) {
    if(in->len == in->allocated)
        double_size_str(in);
    in->text[in->len] = a;
    in->len++;
}

void pull_str(tstring *in, int n) {
    int i;
    for(i=n; i<in->len; i++)
        in->text[i-n] = in->text[i];
    in->len -= n;
}

void strrev(tstring *in) {
    int i, j;
    char a;

    j = in->len-1;
    for(i=0; i<in->len/2; i++) {
        a = in->text[i];
        in->text[i] = in->text[j];
        in->text[j] = a;
        j--;
    }
}

void merge_str(tstring *in1, tstring *in2) {
    int i;
    for(i=0; i<in2->len; i++)
        push_str(in1, in2->text[i]);
    /*free_str(in2);*/
}

void free_str(tstring *in) {
    free(in->text);
}
