#include "sneakstack.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int int_equal(int a, int b) { return (a - b) == 0; };
static int size_equal(size_t a, size_t b) { return a == b; };

static int ptr_not_null(void *ptr, char *message) {
    bool verdict = ptr != NULL;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int ptr_equal(void *ptr_a, void *ptr_b, char *message) {
    bool verdict = ptr_a == ptr_b;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

void test_create_stack_small(void) {
    stack_t *s = stack_new(3);
    assert(int_equal(s->capacity, 3));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s, "Must allocate a new stack"));

    free(s->data);
    free(s);
}

void test_create_stack_large(void) {
    stack_t *s = stack_new(100);
    assert(int_equal(s->capacity, 100));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s, "Must allocate a new stack"));

    free(s->data);
    free(s);
}

void test_push_stack(void) {
    stack_t *s = stack_new(2);
    assert(ptr_not_null(s, "Must allocate a new stack"));
    assert(int_equal(s->capacity, 2));
    assert(int_equal(s->count, 0));

    int a = 1;
    stack_push(s, &a);
    stack_push(s, &a);
    assert(int_equal(s->count, 2));
    assert(ptr_equal(s->data[0], &a, "Element inserted to the stack"));

    free(s->data);
    free(s);
}

void test_push_double_capacity(void) {
    stack_t *s = stack_new(2);
    assert(ptr_not_null(s, "Must allocate a new stack"));
    assert(int_equal(s->capacity, 2));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s->data, "Allocates stack data"));

    int a = 1;
    stack_push(s, &a);
    stack_push(s, &a);
    assert(int_equal(s->count, 2));
    assert(int_equal(s->capacity, 2));

    stack_push(s, &a);
    assert(int_equal(s->count, 3));
    assert(int_equal(s->capacity, 4));

    assert(size_equal(s->capacity * sizeof(void *), 4 * sizeof(void *)));

    free(s->data);
    free(s); 
}

void test_push_multiple_values(void) {
    stack_t *s = stack_new(2);
    assert(ptr_not_null(s->data, "Allocates stack data"));

    int one = 1 ;
    int two = 2 ;
    int three = 3 ;
    stack_push(s, &one);
    stack_push(s, &two);
    stack_push(s, &three);

    assert(int_equal(s->count, 3));
    assert(int_equal(s->capacity, 4));
    assert(ptr_equal(s->data[0], &one, "Element inserted to the stack"));
    assert(ptr_equal(s->data[1], &two, "Element inserted to the stack"));
    assert(ptr_equal(s->data[2], &three, "Element inserted to the stack"));

    free(s->data); 
    free(s);
}

void test_pop_stack(void) {
    stack_t *s = stack_new(2);
    assert(ptr_not_null(s, "Must allocate a new stack"));

    assert(int_equal(s->capacity, 2));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s->data, "Allocates stack data"));

    int one = 1;
    int two = 2;
    int three = 3;

    stack_push(s, &one);
    stack_push(s, &two);

    assert(int_equal(s->capacity, 2));
    assert(int_equal(s->count, 2));
    
    stack_push(s, &three);
    assert(int_equal(s->capacity, 4));
    assert(int_equal(s->count, 3));

    int *popped = stack_pop(s);
    assert(int_equal(*popped, 3));
    assert(int_equal(s->count, 2));

    popped = stack_pop(s);
    assert(int_equal(*popped, 2));
    assert(int_equal(s->count, 1));
     
    popped = stack_pop(s);
    assert(int_equal(*popped, 1));
    assert(int_equal(s->count, 0));

    popped = stack_pop(s);
    assert(popped == NULL);

    free(s->data);
    free(s); 
}

void test_pop_stack_empty(void) {
    stack_t *s = stack_new(2);
    assert(ptr_not_null(s, "Must allocate a new stack"));

    assert(int_equal(s->capacity, 2));
    assert(int_equal(s->count, 0));
    assert(ptr_not_null(s->data, "Allocates stack data"));

    int *popped = stack_pop(s);
    assert(popped == NULL);
    free(s->data);
    free(s); 
}

int main(void) {
    test_create_stack_small();
    test_create_stack_large();
    test_push_stack();
    test_push_double_capacity();
    test_push_multiple_values();
    test_pop_stack();
    test_pop_stack_empty();
    printf("All tests passed.\n");
    return 0;
}
