#include "weighted_dict.h"
#include "dict.h"

void huffman(weighted_dict *in) {
    int i;
    for(i=0; i<in->len-1; i++) {
        append_char_all(&in->dicts[i], '0');
        append_char_all(&in->dicts[i+1], '1');
        merge_on_start(in, i);
        move_value(in, i);
    }
    for(i=0; i<in->dicts[in->len-1].len; i++)
        strrev(&in->dicts[in->len-1].values[i]);
}