#include "tstring.h"
#include <stdlib.h>
#include <stdio.h>

/*All checked - no leaks*/

void allocate_str(tstring *in, int n) { /*Allocates string*/
    in->text = calloc(n, sizeof(char));
    in->allocated = n;
}

void double_size_str(tstring *in) { /*Doubles size of string*/
    in->allocated *= 2;
    in->text = realloc(in->text, sizeof(char) * in->allocated);
}

/*void tidy_str(tstring *in) { Unused
    int i;
    for(i=in->len; i<in->allocated; i++)
        in->text[i] = 0;
}*/

void push_str(tstring *in, char a) { /*Adds char on end, double_size if too small*/
    if(in->len == in->allocated)
        double_size_str(in);
    in->text[in->len] = a;
    in->len++;
}

void pull_str(tstring *in, int n) { /*Takes n first characters from string*/
    int i;
    for(i=n; i<in->len; i++)
        in->text[i-n] = in->text[i];
    in->len -= n;
}

void strrev(tstring *in) { /*Reverses string*/
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

void merge_str(tstring *in1, tstring *in2) { /*Adds content of secound string to first*/
    int i;
    for(i=0; i<in2->len; i++)
        push_str(in1, in2->text[i]);
    /*free_str(in2);*/
}

void write_str(FILE *f_out, tstring *in) { /*writes 8 bits from in to f_out*/
    int i, j, k;
    #ifdef DEBUG
    char c[8];
    #endif
    while(in->len>=8) {
            j = 0;
            k = 1;
            for(i=7; i>=0; i--) {
                j += (in->text[i] - 48) * k;
                k *= 2;
                #ifdef DEBUG
                c[i] = in->text[i];
                #endif
            }
            fwrite(&j, sizeof(char), 1, f_out);
            #ifdef DEBUG
            printf("%s\n", c);
            #endif
            pull_str(in, 8);
        }

}

void free_str(tstring *in) { /*frees string*/
    free(in->text);
}
