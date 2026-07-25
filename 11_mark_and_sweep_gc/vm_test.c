#include "sneknew.h"
#include "snekobject.h"
#include "vm.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    assert(int_equal(vm->frames->count, 0));
    assert(int_equal(vm->objects->count, 0));
    vm_free(vm);
}

void test_vm_free(void) {
    vm_t *vm = vm_new();
    vm_free(vm);
}

void test_vm_new_frame(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    assert(ptr_not_null(frame->references, "References must be allocated"));
    assert(int_equal(frame->references->count, 0));
    assert(frame->references->capacity > 0);
    assert(ptr_not_null(frame->references->data,
                        "References stack backing array must be allocated"));
    vm_free(vm);
}

void test_new_object(void) {
    vm_t *vm = vm_new();
    snek_object_t *obj = new_snek_integer(vm, 5);
    assert(int_equal(obj->kind, INTEGER));
    assert(ptr_not_null(vm->objects->data[0], "Object must be allocated"));
    assert(ptr_equal(vm->objects->data[0], obj, "Object must be tracked"));
    vm_free(vm);
}

void test_array_freed(void) {
    vm_t *vm = vm_new();
    new_snek_array(vm, 3);
    vm_free(vm);
}

void test_frames_are_freed(void) {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_new_frame(vm);
    vm_new_frame(vm);
    vm_free(vm);
}

void test_one_ref(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    snek_object_t *obj = new_snek_integer(vm, 10);
    assert(int_equal(frame->references->count, 0));
    frame_reference_object(frame, obj);
    assert(int_equal(frame->references->count, 1));
    assert(ptr_equal(obj, frame->references->data[0], "Should be same object"));
    vm_free(vm);
}

void test_multi_ref(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    snek_object_t *obj1 = new_snek_integer(vm, 10);
    snek_object_t *obj2 = new_snek_integer(vm, 11);

    assert(int_equal(frame->references->count, 0));
    frame_reference_object(frame, obj1);
    frame_reference_object(frame, obj2);
    assert(int_equal(frame->references->count, 2));
    assert(
        ptr_equal(obj1, frame->references->data[0], "Should be same object"));
    assert(
        ptr_equal(obj2, frame->references->data[1], "Should be same object"));
    vm_free(vm);
}

void test_is_marked_field_exists(void) {
    vm_t *vm = vm_new();
    snek_object_t *obj1 = new_snek_integer(vm, 10);
    snek_object_t *obj2 = new_snek_integer(vm, 20);
    (void)obj1->is_marked;
    (void)obj2->is_marked;
    vm_free(vm);
}

void test_is_marked_is_false(void) {
    vm_t *vm = vm_new();
    snek_object_t *obj1 = new_snek_integer(vm, 10);
    snek_object_t *obj2 = new_snek_integer(vm, 20);
    assert(obj1->is_marked == false);
    assert(obj2->is_marked == false);
    vm_free(vm);
}

void test_mark_single_frame(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    snek_object_t *obj1 = new_snek_integer(vm, 10);
    snek_object_t *obj2 = new_snek_integer(vm, 20);
    mark(vm);
    // should not be marked because not in frame
    assert(obj1->is_marked == false);
    assert(obj2->is_marked == false);

    frame_reference_object(frame, obj1);
    frame_reference_object(frame, obj2);

    mark(vm);
    // after adding and marking should be marked
    assert(obj1->is_marked == true);
    assert(obj2->is_marked == true);
    vm_free(vm);
}

void test_mark_multi_frame(void) {
    vm_t *vm = vm_new();
    frame_t *frame1 = vm_new_frame(vm);
    frame_t *frame2 = vm_new_frame(vm);

    snek_object_t *obj1 = new_snek_integer(vm, 10);
    snek_object_t *obj2 = new_snek_integer(vm, 20);
    snek_object_t *obj3 = new_snek_string(vm, "third");

    frame_reference_object(frame1, obj1);
    frame_reference_object(frame1, obj2);
    frame_reference_object(frame2, obj3);

    mark(vm);
    assert(obj1->is_marked == true);
    assert(obj2->is_marked == true);
    assert(obj3->is_marked == true);
    vm_free(vm);
}

int main(void) {
    test_vm_new();
    test_vm_free();
    test_vm_new_frame();
    test_new_object();
    test_array_freed();
    test_frames_are_freed();
    test_one_ref();
    test_multi_ref();
    test_is_marked_field_exists();
    test_is_marked_is_false();
    test_mark_multi_frame();
    test_mark_multi_frame();
    printf("All tests passed.\n");
    return 0;
}
