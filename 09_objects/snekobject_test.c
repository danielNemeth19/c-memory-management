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

static int ptr_not_equal(void *ptr1, void *ptr2, char *message) {
    bool verdict = ptr1 != ptr2;
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
    printf("All tests passed.\n");
    return 0;
}
