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

void test_trace_vector(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *x = new_snek_integer(vm, 5);
    snek_object_t *y = new_snek_integer(vm, 5);
    snek_object_t *z = new_snek_integer(vm, 5);
    snek_object_t *vector = new_snek_vector3(vm, x, y, z);

    // nothing is marked yet
    assert(x->is_marked == false);
    assert(y->is_marked == false);
    assert(z->is_marked == false);
    assert(vector->is_marked == false);

    // after referencing and marking, the
    // vector should be marked, but not the contents
    frame_reference_object(frame, vector);
    mark(vm);
    assert(x->is_marked == false);
    assert(y->is_marked == false);
    assert(z->is_marked == false);
    assert(vector->is_marked == true);

    // after tracing all objects needs to be marked
    trace(vm);
    assert(x->is_marked == true);
    assert(y->is_marked == true);
    assert(z->is_marked == true);
    assert(vector->is_marked == true);

    vm_free(vm);
}

void test_trace_array(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *item_1 = new_snek_integer(vm, 5);
    snek_object_t *item_2 = new_snek_integer(vm, 5);
    snek_object_t *item_3 = new_snek_integer(vm, 5);
    snek_object_t *array = new_snek_array(vm, 3);

    snek_array_set(array, 0, item_1);
    snek_array_set(array, 1, item_2);
    snek_array_set(array, 2, item_3);

    // nothing is marked yet
    assert(item_1->is_marked == false);
    assert(item_2->is_marked == false);
    assert(item_3->is_marked == false);
    assert(array->is_marked == false);

    // after referencing and marking, the
    // array should be marked, but not the contents
    frame_reference_object(frame, array);
    mark(vm);
    assert(item_1->is_marked == false);
    assert(item_2->is_marked == false);
    assert(item_3->is_marked == false);
    assert(array->is_marked == true);

    // after tracing all objects needs to be marked */
    trace(vm);
    assert(item_1->is_marked == true);
    assert(item_2->is_marked == true);
    assert(item_3->is_marked == true);
    assert(array->is_marked == true);

    vm_free(vm);
}

void test_trace_nested(void) {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *array = new_snek_array(vm, 2);
    snek_object_t *obj1 = new_snek_string(vm, "test 1");
    snek_object_t *obj2 = new_snek_string(vm, "test 2");

    snek_array_set(array, 0, obj1);
    snek_array_set(array, 1, obj2);

    snek_object_t *array2 = new_snek_array(vm, 2);
    snek_object_t *obj3 = new_snek_string(vm, "test 1");
    snek_object_t *obj4 = new_snek_string(vm, "test 2");

    snek_array_set(array2, 0, obj3);
    snek_array_set(array2, 1, obj4);

    snek_object_t *combined_array = new_snek_array(vm, 2);
    snek_array_set(combined_array, 0, array);
    snek_array_set(combined_array, 1, array2);

    frame_reference_object(frame, combined_array);
    mark(vm);
    trace(vm);

    assert(array->is_marked == true);
    assert(obj1->is_marked == true);
    assert(obj2->is_marked == true);
    assert(array2->is_marked == true);
    assert(obj3->is_marked == true);
    assert(obj4->is_marked == true);
    vm_free(vm);
}

void test_trace_mark_object_already_marked(void) {
    vm_t *vm = vm_new();
    stack_t *gray_objects = stack_new(8);
    snek_object_t *obj = new_snek_integer(vm, 7);

    assert(ptr_not_null(gray_objects, "Must be allocated"));
    assert(ptr_not_null(obj, "Must be allocated"));

    obj->is_marked = true;
    trace_mark_object(gray_objects, obj);
    assert(gray_objects->count == 0);

    stack_free(gray_objects);
    vm_free(vm);
}

void test_trace_unreachable_cycle(void) {
    vm_t *vm = vm_new();
    snek_object_t *unreachable = new_snek_array(vm, 1);
    snek_array_set(unreachable, 0, unreachable);

    mark(vm);
    trace(vm);
    assert(unreachable->is_marked == false);
    vm_free(vm);
}

void test_simple_collect_garbage(void) {
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);
    snek_object_t *s = new_snek_string(vm, "I wish I knew how to type");
    frame_reference_object(f1, s);
    // nothing should be collected because the frame haven't be freed yet
    // what should happen:
    //  - mark will mark the object, as the frame is pushed
    //  - in trace, nothing really to do as obj is a string - there's no nested
    //  object to mark
    //  - in sweep, the object is not freed as it's is marked -> `is_marked` is
    //  set to false (so next run of mark can handle it)
    vm_collect_garbage(vm);
    assert(int_equal(vm->objects->count, 1));
    assert(vm->objects->data[0] == s);

    // freeing frame -> the frames stack of pointers is freed, so obj is
    // considered as not reachable
    //  - mark will not mark the object, as frame is gone
    //  - in trace, obj is skipped in processing since last sweep `is_marked` is
    //  false
    //  - now in sweep, the object is freed as it's not marked
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    assert(int_equal(vm->objects->count, 0));
    vm_free(vm);
}

void test_full_collect_garbage(void) {
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);
    frame_t *f2 = vm_new_frame(vm);
    frame_t *f3 = vm_new_frame(vm);

    snek_object_t *s1 = new_snek_string(vm, "This string goes to frame1");
    frame_reference_object(f1, s1);

    snek_object_t *s2 = new_snek_string(vm, "This string goes to frame1");
    frame_reference_object(f2, s2);

    snek_object_t *s3 = new_snek_string(vm, "This string goes to frame1");
    frame_reference_object(f3, s3);

    snek_object_t *i1 = new_snek_integer(vm, 11);
    snek_object_t *i2 = new_snek_integer(vm, 22);
    snek_object_t *i3 = new_snek_integer(vm, 33);
    snek_object_t *v = new_snek_vector3(vm, i1, i2, i3);

    frame_reference_object(f2, v);
    frame_reference_object(f3, v);

    assert(int_equal(vm->objects->count, 7));

    // only free the top frame (f3)
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    // only s3 should be gone
    assert(int_equal(vm->objects->count, 6));

    // freeing frame f2 -> 5 more objects should be gone, only s1 should stay
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    assert(int_equal(vm->objects->count, 1));
    assert(vm->objects->data[0] == s1);

    // freeing last frame -> all should be gone
    frame_free(vm_frame_pop(vm));
    vm_collect_garbage(vm);
    assert(int_equal(vm->objects->count, 0));
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
    test_trace_vector();
    test_trace_array();
    test_trace_nested();
    test_trace_mark_object_already_marked();
    test_simple_collect_garbage();
    test_full_collect_garbage();
    printf("All tests passed.\n");
    return 0;
}
