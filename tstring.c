#include "tstring.h"

#include <stdio.h>
#include <stdlib.h>

/*allocate String with n spaces for chars*/
void allocateString(String *in, int n) {
    in->text = calloc(n, sizeof(char));
    in->alloc = n;
    in->len = 0;
}

/*double allocation of String*/
void doubleStringSize(String *in) {
    in->alloc *= 2;
    in->text = realloc(in->text, sizeof(char) * in->alloc);
}

/*pushes char at the end of String*/
void pushString(String *in, char c) {
    if(in->len==in->alloc)
        doubleStringSize(in);
    in->text[in->len++] = c;
}

/*removes n first characters of String*/
void pullString(String *in, int n) {
    int i;
    for(i=n; i<in->len; i++)
        in->text[i-n] = in->text[i];
    in->len -= n;
}

/*reverses String*/
void reverseString(String *in) {
    int i;
    char c;
    for(i=0; i<in->len; i++) {
        c = in->text[i];
        in->text[i] = in->text[in->len - i];
        in->text[in->len - 1] = c;
    }
}

/*merges String in to String out*/
void mergeString(String *in, String *out) {
    int i;
    for(i=0; i<in->len; i++)
        pushString(out, in->text[i]);
}

/*writes String to file in binary*/
void writeOut(FILE *f, String *in) {
    int i;
    while(in->len>=8) {
        i = (in->text[0] - 48) * 128 + (in->text[1] - 48) * 64 + (in->text[2] - 48) * 32 + (in->text[3] - 48) * 16 + (in->text[4] - 48) * 8 + (in->text[5] - 48) * 4 + (in->text[6] - 48) * 2 + (in->text[7] - 48);
        fwrite(&i, sizeof(char), 1, f);
        pullString(in, 8);
    }
}

void freeString(String *in) {
    free(in->text);
}