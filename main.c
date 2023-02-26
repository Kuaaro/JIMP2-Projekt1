#include "tstring.h"
#include "dict.h"
#include "weighted_dict.h"
#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f_in, *f_out;
    int i, j, k;
    weighted_dict wd;
    tstring temp, *hash_map;

    allocate_and_fill_weighted_dict(&wd, 256);

    f_in = fopen("test.txt", "rb");
    f_out = fopen("out.huff", "wb");

    while((i = getc(f_in)) != EOF)
        add_count(&wd, i);
    rewind(f_in);

    sort_weighted_dict(&wd);

    for(i=0; i<wd.len; i++)
        if(wd.weights[i]==0) {
            free_dict(&wd.dicts[i]);
        } else {
            break;
        }

    huffman_on_start(&wd, i);
    free(wd.weights);

    hash_map = calloc(256, sizeof(tstring));
    j = 0;
    for(i=0; i<wd.dicts[255].len; i++) {
        j = j < wd.dicts[255].values[i].len ? wd.dicts[255].values[i].len : j;
        hash_map[wd.dicts[255].keys[i]] = wd.dicts[255].values[i];
        printf("key: %c, value: %s\n", wd.dicts[255].keys[i], wd.dicts[255].values[i].text);
    }
    
    allocate_str(&temp, j + 7);

    while((i = getc(f_in)) != EOF) {
        merge_str(&temp, &hash_map[i]);
        while(temp.len>=8) {
            j = 0;
            k = 1;
            for(i=7; i>=0; i--) {
                j += (temp.text[i] - 48) * k;
                k *= 2;
            }
            fwrite(&j, sizeof(char), 1, f_out);
            printf("%s %c\n", temp.text, j);
            pull_str(&temp, 8);
        }
    }

    push_str(&temp, '1');
    for(i=0; i<8-temp.len; i++)
        push_str(&temp, '0');
    j = 0;
    k = 1;
    for(i=7; i>=0; i--) {
        j += (temp.text[i] - 48) * k;
        k *= 2;
    }
    fwrite(&j, sizeof(char), 1, f_out);
    printf("%s %c\n", temp.text, j);

    free_dict(&wd.dicts[255]);
    free(wd.dicts);
    free(hash_map);

    free_str(&temp);

    fclose(f_in);
    fclose(f_out);

    return 0;
}
