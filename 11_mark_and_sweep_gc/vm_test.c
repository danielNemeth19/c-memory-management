#include "vm.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

static int int_equal(int a, int b) { return (a - b) == 0; };

static int float_equal(float a, float b) {
    const float epsilon = 1e-6f;
    return (a - b < epsilon) && (b - a < epsilon);
}

static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

static int ptr_not_null(void *ptr, char *message) {
    bool verdict = ptr != NULL;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int ptr_is_null(void *ptr, char *message) {
    bool verdict = ptr == NULL;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int ptr_not_equal(void *ptr1, void *ptr2, char *message) {
    bool verdict = ptr1 != ptr2;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int ptr_equal(void *ptr1, void *ptr2, char *message) {
    bool verdict = ptr1 == ptr2;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

void test_vm_new(void) {
    vm_t *vm = vm_new();
    assert(int_equal(vm->frames->capacity, 8));
    assert(int_equal(vm->objects->capacity, 8));
    vm_free(vm);
}

void test_vm_free(void) {
    vm_t *vm = vm_new();
    vm_free(vm);
}

int main(void) {
    test_vm_new();
    test_vm_free();
    printf("All tests passed.\n");
    return 0;
}
