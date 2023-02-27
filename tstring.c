#include "tstring.h"
#include <stdlib.h>
#include <stdio.h>

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

void write_str(FILE *f_out, tstring *in) {
    int i, j, k;
    char c[8];
    while(in->len>=8) {
            j = 0;
            k = 1;
            for(i=7; i>=0; i--) {
                j += (in->text[i] - 48) * k;
                k *= 2;
                c[i] = in->text[i];
            }
            fwrite(&j, sizeof(char), 1, f_out);
            printf("%s\n", c);
            pull_str(in, 8);
        }

}

void free_str(tstring *in) {
    free(in->text);
}
