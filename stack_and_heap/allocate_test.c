#include "allocate.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test_allocate_scalar_array_size(void) {
    int size = 5;
    int multiplier = 2;

    int expected_array[5] = {0, 2, 4, 6, 8};

    int *result = allocate_scalar_array(size, multiplier);
    for (int i = 0; i < size; i++) {
        assert(result[i] == expected_array[i]);
    }
    free(result);
}

void test_allocate_scalar_array_zero_multiplier(void) {
    int size = 5;
    int multiplier = 0;

    int expected_array[5] = {0, 0, 0, 0, 0};

    int *result = allocate_scalar_array(size, multiplier);
    for (int i = 0; i < size; i++) {
        assert(result[i] == expected_array[i]);
    }
    free(result);
}

void test_allocate_too_much(void) {
    int size = (64 * 1024 * 1024) / sizeof(int);
    int multiplier = 1;

    int *result = allocate_scalar_array(size, multiplier);
    assert(result != NULL);
    assert(result[0] == 0);
    assert(result[size - 1] == size - 1);
    free(result);
}

int main(void) {
    test_allocate_scalar_array_size();
    test_allocate_scalar_array_zero_multiplier();
    test_allocate_too_much();
    printf("All tests passed.\n");
    return 0;
}
