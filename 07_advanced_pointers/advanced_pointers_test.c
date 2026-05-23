#include "advanced_pointers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool assert_not_null(void *ptr) {
    if (ptr == NULL) {
        return false;
    }
    return true;
}

static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

static int int_equal(int a, int b) { return (a - b) == 0; };

void test_allocate(void) {
    int *pointer = NULL;
    allocate_int(&pointer, 10);

    assert_not_null(pointer);
    assert(int_equal(*pointer, 10));
    free(pointer);
}

void test_does_not_overwrite(void) {
    int value = 5;
    int *pointer = &value;
    printf("pointer's value before: %p\n", pointer);

    allocate_int(&pointer, 20);

    // pointer's value is changed by the function
    // since it will point to the allocated int now
    printf("pointer's value after: %p\n", pointer);
    assert(int_equal(value, 5));
    assert_not_null(pointer);
    assert(int_equal(*pointer, 20));
    free(pointer);
}

int main(void) {
    test_allocate();
    test_does_not_overwrite();
    printf("All tests passed.\n");
    return 0;
}
