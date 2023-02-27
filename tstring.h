#ifndef TSTRING_H
#define TSTRING_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *text;
    int len;
    int allocated;
} tstring;

void allocate_str(tstring *in, int n);

void double_size_str(tstring *in);

/*void tidy_str(tstring *in); Unused*/

void push_str(tstring *in, char a);

void pull_str(tstring *in, int n);

void strrev(tstring *in);

void merge_str(tstring *in1, tstring *in2);

void write_str(FILE *f_out, tstring *in);

void free_str(tstring *in);

#endif
