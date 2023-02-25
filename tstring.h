#ifndef TSTRING_H
#define TSTRING_H

#include <stdlib.h>

typedef struct {
    char *text;
    int len;
    int allocated;
} tstring;

void strrev(tstring *in);

void allocate_str(tstring *in, int n);

void double_size_str(tstring *in);

void tidy_str(tstring *in);

void push_str(tstring *in, char a);

void free_str(tstring *in);
#endif


