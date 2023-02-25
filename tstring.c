#include "tstring.h"

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

void allocate_str(tstring *in, int n) {
    in->text = malloc(sizeof(char) * n);
    in->allocated = n;
}

void double_size_str(tstring *in) {
    in->allocated *= 2;
    in->text = realloc(in->text, sizeof(char) * in->allocated);
}

void tidy_str(tstring *in) {
    int i;
    for(i=in->len; i<in->allocated; i++)
        in->text[i] = 0;
}

void push_str(tstring *in, char a) {
    if(in->len == in->allocated)
        double_size_str(in);
    in->text[in->len] = a;
    in->len++;
}

void free_str(tstring *in) {
    free(in->text);
}
