#include "tstring.h"
#include "dict.h"
#include "weighted_dict.h"
#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /*Init*/
    FILE *f_in, *f_out;
    int i, j, k;
    weighted_dict wd;
    tstring temp, temp2, *hash_map;

    /*Checks if file name is given*/
    if(argc==1) {
        printf("%s: file name not given\n", argv[0]);
        return 1;
    }

    /*checks if file exists*/
    if((f_in = fopen(argv[1], "rb")) == NULL) {
        printf("%s: file '%s' not found\n", argv[0], argv[1]);
        return 1;
    }

    /*checks if f_in is empty*/
    i=getc(f_in);
    j=0;
    if(i==-1) {
        printf("%s: file '%s' is empty\n", argv[0], argv[1]);
        fclose(f_in);
        return 1;
    }

    /*checks if i is new line char*/
    if(i!=10)
        j=1;

    /*allocates weighted dict and adds first char*/
    allocate_and_fill_weighted_dict(&wd, 256);
    add_count(&wd, i);

    /*goes through whole file, checking, if there is at least 1 char different than newline*/
    while((i = getc(f_in)) != EOF) {
        add_count(&wd, i);
        if(i!=10)
            j=1;
    }

    /*if there are only new line char, frees allocations and terminates*/
    if(j!=1) {
        printf("%s: file '%s' consist of only new line characters\n", argv[0], argv[1]);
        for(i=0; i<wd.allocated; i++)
            free_dict(&wd.dicts[i]);
        free(wd.weights);
        free(wd.dicts);
        fclose(f_in);
        return 1;
    }

    /*rewinds file*/
    rewind(f_in);

    /*sorts dict*/
    sort_weighted_dict(&wd);

    /*moves start until it only affects chars contained in file*/
    for(i=0; i<wd.len; i++)
        if(wd.weights[i]==0) {
            free_dict(&wd.dicts[i]);
        } else {
            break;
        }

    /*huffmans weighted_dict*/
    huffman_on_start(&wd, i);
    free(wd.weights);

    /*creates hashmap of all characters, that are in huffman*/
    hash_map = calloc(256, sizeof(tstring));
    j = 0;
    for(i=0; i<wd.dicts[255].len; i++) {
        j = j < wd.dicts[255].values[i].len ? wd.dicts[255].values[i].len : j;
        hash_map[wd.dicts[255].keys[i]] = wd.dicts[255].values[i];
        #ifdef DEBUG
        printf("key: %c, value: %s\n", wd.dicts[255].keys[i], wd.dicts[255].values[i].text);
        #endif
    }

    /*allocates strings used in writing to file*/
    allocate_str(&temp, (j > 8 ? j : 8) + 7);
    allocate_str(&temp2, 8);

    f_out = fopen("out.huff", "wb");

    /*encodes keys to characters*/
    for(i=0; i<256; i++) {
        j = hash_map[i].len;
        for(k=0; k<8; k++) {
            push_str(&temp2, j%2 + '0');
            j /= 2;
        }
        strrev(&temp2);
        merge_str(&temp, &temp2);
        pull_str(&temp2, 8);
        write_str(f_out, &temp);
        if(hash_map[i].len) {
            merge_str(&temp, &hash_map[i]);
            write_str(f_out, &temp);
        }
    }

    free_str(&temp2);

    /*compresses characters from f_in to f_out*/
    while((i = getc(f_in)) != EOF) {
        merge_str(&temp, &hash_map[i]);
        write_str(f_out, &temp);
    }

    /*completes string, fills up to 8 bytes, starting with 1, ending with 0s*/
    push_str(&temp, '1');
    while(temp.len%8!=0)
        push_str(&temp, '0');
    write_str(f_out, &temp);

    /*frees and closes*/
    free_dict(&wd.dicts[255]);

    free(wd.dicts);
    free(hash_map);

    free_str(&temp);

    fclose(f_in);
    fclose(f_out);

    return 0;
}
