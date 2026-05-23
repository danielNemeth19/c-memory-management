#include "allocate.h"
#include <stdio.h>
#include <stdlib.h>

int *allocate_scalar_array(int size, int multiplier) {
    int *ptr = malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        ptr[i] = i * multiplier;
    }
    return ptr;
}
