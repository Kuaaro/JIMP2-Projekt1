#ifndef WEIGHTED_STRING_POINTERS_H
#define WEIGHTED_STRING_POINTERS_H

#include "tstring.h"

#include <stdlib.h>

typedef struct {
    int len, weight;
    String **pointers;
} WeightedStringPointers;

void allocateWeightedStringPointers(WeightedStringPointers *in, int n);

#endif