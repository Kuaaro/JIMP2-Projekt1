#include "tstring.h"
#include "dict.h"
#include "weighted_dict.h"
#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *f_in, *f_out;
    int i, j, k;
    weighted_dict wd;
    tstring temp, temp2, *hash_map;

    if(argc==1) {
        printf("%s: file name not given\n", argv[0]);
        return 1;
    }

    if((f_in = fopen(argv[1], "rb")) == NULL) {
        printf("%s: file '%s' not found\n", argv[0], argv[1]);
        return 1;
    }
    allocate_and_fill_weighted_dict(&wd, 256);
    
    j=0;
    while((i = getc(f_in)) != EOF) {
        add_count(&wd, i);
        j++;
    }

    if(j==0) {
        printf("%s: file '%s' is empty\n", argv[0], argv[1]);
        free_weighted_dict(&wd);
        fclose(f_in);
        return 1;
    }
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
    
    allocate_str(&temp, (j > 8 ? j : 8) + 7);
    allocate_str(&temp2, 8);

    f_out = fopen("out.huff", "wb");

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

    while((i = getc(f_in)) != EOF) {
        merge_str(&temp, &hash_map[i]);
        write_str(f_out, &temp);
    }

    push_str(&temp, '1');
    for(i=0; i<8-temp.len; i++)
        push_str(&temp, '0');
    write_str(f_out, &temp);

    free_dict(&wd.dicts[255]);
    free(wd.dicts);
    free(hash_map);

    free_str(&temp);

    fclose(f_in);
    fclose(f_out);

    return 0;
}
