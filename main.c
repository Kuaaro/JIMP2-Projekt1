#include "tstring.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    int i, ct = 1, weights[256], lenghts[256];
    String mainString[256], **pointers[256];
    FILE *f_in, f_out;

    f_in = fopen("test.txt", "rb");

    for(i=0; i<256; i++) {
        weights[i] = 0;
        lenghts[i] = 1;
        pointers[i] = malloc(sizeof(String*));
        allocateString(&mainString[i], 1);
    }

    while(ct) {
        ct = 0;
        for(i=0; i<256; i++) {
            
        }
    }

    while((i = getc(f_in)) != EOF)
        weights[i]++;

    for(i=0; i<256; i++) {
        printf("%d ", weights[i]);
        freeString(&mainString[i]);
        free(pointers[i]);
    }
    printf("\n");

    fclose(f_in);

    return 0;
}