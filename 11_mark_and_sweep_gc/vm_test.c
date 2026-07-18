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

void test_new_vm(void) {
    vm_t *vm = vm_new();
    assert(int_equal(vm->frames->count, 0));
    vm_new_frame(vm);
    assert(int_equal(vm->frames->count, 1));
    frame_free(vm->frames->data[0]);
    vm_free(vm);
}

void test_vm_new_frame(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    assert(ptr_not_null(frame->references, "References must be allocated"));
    assert(int_equal(frame->references->count, 0));
    assert(frame->references->capacity > 0);
    assert(ptr_not_null(frame->references->data, "References stack backing array must be allocated"));
    frame_free(frame);
    vm_free(vm);
}

int main(void) {
    test_vm_new();
    test_vm_free();
    test_new_vm();
    test_vm_new_frame();
    printf("All tests passed.\n");
    return 0;
}
