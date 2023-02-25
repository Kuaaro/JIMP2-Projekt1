#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "tstring.h"
#include "weighted_dict.h"
#include "huffman.h"

int main() {
    int a;
    weighted_dict d;
    dict di;

    FILE *f = fopen("test.txt", "rb");

    d.len = 0;

    allocate_weighted_dict(&d, 1);

    while((a = getc(f)) != EOF)
        add_count(&d, a);

    sort_weighted_dict(&d);

    /*for(a=0; a<d.len; a++)
        printf("weight: %d, key: %d\n", d.weights[a], d.dicts[a].keys[0]);*/

    huffman(&d);
    di = d.dicts[d.len-1];
    free(d.weights);

    for(a=0; a<d.dicts[d.len-1].len; a++)
        printf("key: \'%d\', value: %s\n", di.keys[a], di.values[a].text);

    free_dict(&di);
    fclose(f);

    return 0;
}
