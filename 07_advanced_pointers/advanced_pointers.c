#include "advanced_pointers.h"
#include <stdlib.h>

void allocate_int(int **pointer_pointer, int value) {
    int *ptr = malloc(sizeof(int));
    *pointer_pointer = ptr;
    *ptr = value;
}
