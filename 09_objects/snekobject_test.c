#include "snekobject.h"
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

void test_integer_constant(void) { assert(int_equal(INTEGER, 0)); }

void test_integer_obj(void) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));

    obj->kind = INTEGER;
    obj->data.v_int = 0;

    assert(int_equal(obj->kind, INTEGER));
    assert(int_equal(obj->data.v_int, 0));
    free(obj);
}

void test_snek_integer_positive(void) {
    snek_object_t *t = new_snek_integer(10);

    assert(int_equal(t->data.v_int, 10));
    assert(int_equal(t->kind, INTEGER));
    free(t);
}

void test_snek_integer_zero(void) {
    snek_object_t *t = new_snek_integer(0);

    assert(int_equal(t->data.v_int, 0));
    assert(int_equal(t->kind, INTEGER));
    free(t);
}

void test_snek_integer_negative(void) {
    snek_object_t *t = new_snek_integer(-10);

    assert(int_equal(t->data.v_int, -10));
    assert(int_equal(t->kind, INTEGER));
    free(t);
}

void test_snek_float_positive(void) {
    snek_object_t *t = new_snek_float(8.23);

    assert(float_equal(t->data.v_float, 8.23));
    assert(float_equal(t->kind, FLOAT));
    free(t);
}

void test_snek_float_zero(void) {
    snek_object_t *t = new_snek_float(0.0);

    assert(float_equal(t->data.v_float, 0.0));
    assert(float_equal(t->kind, FLOAT));
    free(t);
}

void test_snek_float_negative(void) {
    snek_object_t *t = new_snek_float(-10.13);

    assert(float_equal(t->data.v_float, -10.13));
    assert(int_equal(t->kind, FLOAT));
    free(t);
}

void test_snek_string_copied(void) {
    char *input = "Hello World!";
    snek_object_t *obj = new_snek_string(input);

    assert(int_equal(obj->kind, STRING));
    assert(ptr_not_equal(input, obj->data.v_string,
                         "Pointers should be different"));
    assert(string_equal(input, obj->data.v_string));

    free(obj->data.v_string);
    free(obj);
}

void test_snek_vector3_returns_null(void) {
    snek_object_t *obj1 = new_snek_float(10.1);
    snek_object_t *obj2 = new_snek_integer(10);

    snek_object_t *s_obj = new_snek_vector3(obj1, obj2, NULL);
    assert(s_obj == NULL);
}

void test_snek_vector3_multiple_objects(void) {
    snek_object_t *obj1 = new_snek_float(10.1);
    snek_object_t *obj2 = new_snek_integer(10);
    snek_object_t *obj3 = new_snek_string("Blaa");

    snek_object_t *vec = new_snek_vector3(obj1, obj2, obj3);
    assert(ptr_not_null(vec, "Should allocate pointer"));

    assert(obj1 == vec->data.v_vector3.x);
    assert(obj2 == vec->data.v_vector3.y);
    assert(obj3 == vec->data.v_vector3.z);

    assert(float_equal(vec->data.v_vector3.x->data.v_float, 10.1));
    assert(int_equal(vec->data.v_vector3.y->data.v_int, 10));
    assert(string_equal(vec->data.v_vector3.z->data.v_string, "Blaa"));

    free(obj1);
    free(obj2);
    free(obj3);
    free(vec);
}

void test_snek_array_create_empty(void) {
    snek_object_t *obj = new_snek_array(2);

    assert(int_equal(obj->kind, ARRAY));
    assert(int_equal(obj->data.v_array.size, 2));

    free(obj->data.v_array.elements);
    free(obj);
}

void test_snek_array_used_calloc(void) {
    snek_object_t *obj = new_snek_array(2);

    assert(ptr_is_null(obj->data.v_array.elements[0],
                       "Must be allocated as null"));
    assert(ptr_is_null(obj->data.v_array.elements[1],
                       "Must be allocated as null"));
}

void test_snek_array_set_false(void) {
    bool res1 = snek_array_set(NULL, 0, NULL);
    assert(res1 == false);

    snek_object_t *obj = new_snek_array(2);
    bool res2 = snek_array_set(obj, 0, NULL);
    assert(res2 == false);

    snek_object_t *obj_int = new_snek_integer(10);
    snek_object_t *obj_float = new_snek_float(10.10);
    bool res3 = snek_array_set(obj_int, 0, obj_float);
    assert(res2 == false);

    snek_object_t *obj_arr = new_snek_array(2);
    bool res4 = snek_array_set(obj_arr, 10, obj_int);
    assert(res4 == false);

    free(obj);
    free(obj_int);
    free(obj_float);
    free(obj_arr);
}

void test_snek_array_set(void) {
    snek_object_t *obj = new_snek_array(2);

    assert(ptr_is_null(obj->data.v_array.elements[0], "Allocated as null"));
    assert(ptr_is_null(obj->data.v_array.elements[1], "Allocated as null"));

    snek_object_t *int_elem = new_snek_integer(5);
    snek_object_t *float_elem = new_snek_float(10.10);

    snek_array_set(obj, 0, int_elem);
    snek_array_set(obj, 1, float_elem);

    assert(int_equal(obj->data.v_array.elements[0]->data.v_int, 5));
    assert(float_equal(obj->data.v_array.elements[1]->data.v_float, 10.10));

    free(int_elem);
    free(float_elem);
    free(obj->data.v_array.elements);
    free(obj);
}

void test_snek_array_get_null(void) {
    snek_object_t *res1 = snek_array_get(NULL, 1);
    assert(ptr_is_null(res1, "Should return null"));

    snek_object_t *obj_int = new_snek_integer(10);
    snek_object_t *res2 = snek_array_get(obj_int, 1);
    assert(ptr_is_null(res2, "Should return null"));

    snek_object_t *obj_array = new_snek_array(2);
    snek_object_t *obj_char1 = new_snek_string("one");
    snek_object_t *obj_char2 = new_snek_string("two");
    assert(snek_array_set(obj_array, 0, obj_char1));
    assert(snek_array_set(obj_array, 1, obj_char2));
    snek_object_t *res3 = snek_array_get(obj_array, 3);
    assert(ptr_is_null(res3, "Should return null"));

    free(res1);
    free(res2);
    free(obj_int);
    free(obj_char1->data.v_string);
    free(obj_char2->data.v_string);
    free(obj_char1);
    free(obj_char2);
    free(obj_array->data.v_array.elements);
}

void test_snek_array_get_empty_slot(void) {
    snek_object_t *obj = new_snek_array(2);

    snek_object_t *empty = snek_array_get(obj, 0);
    assert(empty == NULL);
}

void test_snek_array_get(void) {
    snek_object_t *obj = new_snek_array(2);
    snek_object_t *first = new_snek_string("First");
    snek_object_t *second = new_snek_integer(3);

    assert(snek_array_set(obj, 0, first));
    assert(snek_array_set(obj, 1, second));

    snek_object_t *retrieved_first = snek_array_get(obj, 0);
    assert(ptr_not_null(retrieved_first, "Should not be null"));
    assert(int_equal(retrieved_first->kind, STRING));
    assert(string_equal(retrieved_first->data.v_string, "First"));
    assert(ptr_equal(first, retrieved_first, "Should be the same object"));

    snek_object_t *retrieved_second = snek_array_get(obj, 1);
    assert(ptr_not_null(retrieved_second, "Should not be null"));
    assert(int_equal(retrieved_second->kind, INTEGER));
    assert(int_equal(retrieved_second->data.v_int, 3));
    assert(ptr_equal(second, retrieved_second, "Should be the same object"));

    free(first->data.v_string);
    free(first);
    free(second);
    free(obj->data.v_array.elements);
    free(obj);
}

void test_snek_length_null(void) {
    int len = snek_length(NULL);
    assert(int_equal(len, -1));
}

void test_snek_length_integer(void) {
    snek_object_t *obj_int = new_snek_integer(10);
    int len = snek_length(obj_int);
    assert(int_equal(len, 1));
}

void test_snek_length_float(void) {
    snek_object_t *obj_float = new_snek_float(10.10);
    int len = snek_length(obj_float);
    assert(int_equal(len, 1));
}

void test_snek_length_string(void) {
    snek_object_t *obj_string = new_snek_string("my string");
    int len = snek_length(obj_string);
    assert(int_equal(len, 9));
    free(obj_string->data.v_string);
    free(obj_string);
}

void test_snek_length_vector(void) {
    snek_object_t *obj1 = new_snek_float(10.1);
    snek_object_t *obj2 = new_snek_integer(10);
    snek_object_t *obj3 = new_snek_string("Blaa");
    snek_object_t *obj_vector3 = new_snek_vector3(obj1, obj2, obj3);
    int len = snek_length(obj_vector3);
    assert(int_equal(len, 3));

    free(obj_vector3->data.v_vector3.x);
    free(obj_vector3->data.v_vector3.y);
    free(obj_vector3->data.v_vector3.z->data.v_string);
    free(obj_vector3->data.v_vector3.z);
    free(obj_vector3);
}

void test_snek_length_array(void) {
    snek_object_t *i = new_snek_integer(1);
    snek_object_t *arr = new_snek_array(4);

    assert(snek_array_set(arr, 0, i));
    assert(snek_array_set(arr, 1, i));
    assert(snek_array_set(arr, 2, i));

    assert(int_equal(arr->data.v_array.size, 4));

    free(i);
    free(arr->data.v_array.elements);
    free(arr);
}

void test_snek_add_null(void) {
    snek_object_t *obj = new_snek_integer(10);
    snek_object_t *null_1 = snek_add(NULL, obj);
    assert(ptr_is_null(null_1, "Should return NULL"));
    snek_object_t *null_2 = snek_add(obj, NULL);
    assert(ptr_is_null(null_2, "Should return NULL"));
}

void test_snek_add_integer(void) {
    snek_object_t *int_part = new_snek_integer(5);

    snek_object_t *int_sum = snek_add(int_part, int_part);
    assert(int_equal(int_sum->kind, INTEGER));
    assert(int_equal(int_sum->data.v_int, 10));

    free(int_part);
    free(int_sum);
}

void test_snek_add_float(void) {
    snek_object_t *int_part = new_snek_integer(5);
    snek_object_t *float_part = new_snek_float(10.5);

    snek_object_t *float_1 = snek_add(int_part, float_part);
    assert(int_equal(float_1->kind, FLOAT));
    assert(float_equal(float_1->data.v_float, 15.5));

    snek_object_t *float_2 = snek_add(int_part, float_part);
    assert(int_equal(float_2->kind, FLOAT));
    assert(float_equal(float_2->data.v_float, 15.5));

    snek_object_t *float_3 = snek_add(float_part, float_part);
    assert(int_equal(float_3->kind, FLOAT));
    assert(float_equal(float_3->data.v_float, 21.0));

    free(int_part);
    free(float_part);
    free(float_1);
    free(float_2);
    free(float_3);
}

void test_snek_add_string_invalid(void) {
    snek_object_t *str_part = new_snek_string("first");
    snek_object_t *null_obj = snek_add(str_part, NULL);
    assert(ptr_is_null(null_obj, "Should return NULL"));

    free(str_part->data.v_string);
    free(str_part);
}

void test_snek_add_string(void) {
    snek_object_t *first_part = new_snek_string("first");
    snek_object_t *second_part = new_snek_string("second");

    snek_object_t *obj = snek_add(first_part, second_part);
    assert(ptr_not_null(obj, "Should not be null"));
    assert(string_equal(obj->data.v_string, "firstsecond"));

    free(first_part->data.v_string);
    free(second_part->data.v_string);
    free(first_part);
    free(second_part);
    free(obj->data.v_string);
    free(obj);
}

void test_snek_add_vector3_invalid(void) {
    snek_object_t *obj1 = new_snek_float(10.1);
    snek_object_t *obj2 = new_snek_integer(10);
    snek_object_t *obj3 = new_snek_string("Blaa");

    snek_object_t *vec = new_snek_vector3(obj1, obj2, obj3);
    snek_object_t *null_obj = snek_add(vec, NULL);
    assert(ptr_is_null(null_obj, "Should return NULL"));

    free(obj1);
    free(obj2);
    free(obj3);
    free(vec);
}

void test_snek_add_vector3(void) {
    snek_object_t *v1_x = new_snek_integer(1);
    snek_object_t *v1_y = new_snek_integer(2);
    snek_object_t *v1_z = new_snek_integer(3);
    snek_object_t *vec1 = new_snek_vector3(v1_x, v1_y, v1_z);

    snek_object_t *v2_x = new_snek_integer(1);
    snek_object_t *v2_y = new_snek_integer(2);
    snek_object_t *v2_z = new_snek_integer(3);
    snek_object_t *vec2 = new_snek_vector3(v2_x, v2_y, v2_z);

    snek_object_t *vec_sum = snek_add(vec1, vec2);

    assert(int_equal(vec_sum->data.v_vector3.x->data.v_int, 2));
    assert(int_equal(vec_sum->data.v_vector3.y->data.v_int, 4));
    assert(int_equal(vec_sum->data.v_vector3.z->data.v_int, 6));

    free(v1_x);
    free(v1_y);
    free(v1_z);
    free(v2_x);
    free(v2_y);
    free(v2_z);
    free(vec_sum);
}

void test_snek_add_array_invalid(void) {
    snek_object_t *arr = new_snek_array(2);
    snek_object_t *arr_elem_1 = new_snek_integer(8);
    snek_object_t *arr_elem_2 = new_snek_integer(7);
    snek_array_set(arr, 0, arr_elem_1);
    snek_array_set(arr, 1, arr_elem_2);

    snek_object_t *null_obj = snek_add(arr, NULL);
    assert(ptr_is_null(null_obj, "Should return NULL"));

    free(arr_elem_1);
    free(arr_elem_2);
    free(arr->data.v_array.elements);
    free(arr);
}


void test_snek_add_array(void) {
    snek_object_t *arr_1 = new_snek_array(2);
    snek_object_t *arr_1_elem_1 = new_snek_integer(8);
    snek_object_t *arr_1_elem_2 = new_snek_integer(7);
    snek_array_set(arr_1, 0, arr_1_elem_1);
    snek_array_set(arr_1, 1, arr_1_elem_2);

    snek_object_t *arr_2 = new_snek_array(2);
    snek_object_t *arr_2_elem_1 = new_snek_integer(6);
    snek_object_t *arr_2_elem_2 = new_snek_integer(5);
    snek_array_set(arr_2, 0, arr_2_elem_1);
    snek_array_set(arr_2, 1, arr_2_elem_2);

    snek_object_t *arr_sum = snek_add(arr_1, arr_2);
    assert(int_equal(arr_sum->data.v_array.size, 4));

    assert(int_equal(arr_sum->data.v_array.elements[0]->data.v_int, 8));
    assert(int_equal(arr_sum->data.v_array.elements[1]->data.v_int, 7));
    assert(int_equal(arr_sum->data.v_array.elements[2]->data.v_int, 6));
    assert(int_equal(arr_sum->data.v_array.elements[3]->data.v_int, 5));

    free(arr_1_elem_1);
    free(arr_1_elem_2);
    free(arr_2_elem_1);
    free(arr_2_elem_2);
    free(arr_1->data.v_array.elements);
    free(arr_2->data.v_array.elements);
    free(arr_sum->data.v_array.elements);
    free(arr_1);
    free(arr_2);
    free(arr_sum);
}

void test_snek_new_int_refcount(void) {
    snek_object_t *int_obj = new_snek_integer(10);
    assert(int_equal(int_obj->refcount, 1));
    free(int_obj);
}

void test_snek_new_float_refcount(void) {
    snek_object_t *float_obj = new_snek_float(2.34);
    assert(int_equal(float_obj->refcount, 1));
    free(float_obj);
}

int main(void) {
    test_integer_constant();
    test_integer_obj();
    test_snek_integer_positive();
    test_snek_integer_zero();
    test_snek_integer_negative();
    test_snek_float_positive();
    test_snek_float_zero();
    test_snek_float_negative();
    test_snek_string_copied();
    test_snek_vector3_returns_null();
    test_snek_vector3_multiple_objects();
    test_snek_array_create_empty();
    test_snek_array_used_calloc();
    test_snek_array_set_false();
    test_snek_array_set();
    test_snek_array_get_null();
    test_snek_array_get_empty_slot();
    test_snek_array_get();
    test_snek_length_null();
    test_snek_length_integer();
    test_snek_length_float();
    test_snek_length_string();
    test_snek_length_vector();
    test_snek_length_array();
    test_snek_add_null();
    test_snek_add_integer();
    test_snek_add_float();
    test_snek_add_string_invalid();
    test_snek_add_string();
    test_snek_add_vector3_invalid();
    test_snek_add_vector3();
    test_snek_add_array_invalid();
    test_snek_add_array();
    test_snek_new_int_refcount();
    test_snek_new_float_refcount();
    printf("All tests passed.\n");
    return 0;
}
