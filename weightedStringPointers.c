#include <stdlib.h>

#include "weightedStringPointers.h"



void allocateWeightedStringPointers(WeightedStringPointers *in, int n) {
    in->pointers = malloc(sizeof(String*) * n);
    in->weight = 0;
    in->len = n;
}