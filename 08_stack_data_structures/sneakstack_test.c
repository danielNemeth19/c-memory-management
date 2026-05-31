#include "sneakstack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int int_equal(int a, int b) { return (a - b) == 0; };

static int ptr_not_null(void *ptr, char *message) {
    bool verdict = ptr != NULL;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

void test_create_stack_small(void) {
    stack_t *s = stack_new(3);
    assert(int_equal(s->capacity, 3));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s, "Allocates the stack data"));

    free(s->data);
    free(s);
}

void test_create_stack_large(void) {
    stack_t *s = stack_new(100);
    assert(int_equal(s->capacity, 100));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s, "Allocates the stack data"));

    free(s->data);
    free(s);
}

int main(void) {
    test_create_stack_small();
    test_create_stack_large();
    printf("All tests passed.\n");
    return 0;
}
