#ifndef TSTRING_H
#define TSTRING_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *text;
    int len;
    int allocated;
} tstring;

void allocate_str(tstring *in, int n); /*Allocates string*/

void double_size_str(tstring *in); /*Doubles size of string*/

/*void tidy_str(tstring *in); Unused*/

void push_str(tstring *in, char a); /*Adds char on end, double_size if too small*/

void pull_str(tstring *in, int n); /*Takes n first characters from string*/

void strrev(tstring *in); /*Reverses string*/

void merge_str(tstring *in1, tstring *in2); /*Adds content of secound string to first*/

void write_str(FILE *f_out, tstring *in); /*writes 8 bits from in to f_out*/

void free_str(tstring *in); /*frees string*/

#endif
