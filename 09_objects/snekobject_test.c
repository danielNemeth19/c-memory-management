#include "snekobject.h"
#include <assert.h>
#include <stdio.h>

static int int_equal(int a, int b) { return (a - b) == 0; };

void test_integer_constant(void) {
    assert(int_equal(INTEGER, 0));
}

void test_integer_obj(void) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));

    obj->kind = INTEGER;
    obj->data.v_int = 0;

    assert(int_equal(obj->kind, INTEGER));
    assert(int_equal(obj->data.v_int, 0));
    free(obj);
}

int main(void) {
    test_integer_constant();
    test_integer_obj();
    printf("All tests passed.\n");
    return 0;
}
