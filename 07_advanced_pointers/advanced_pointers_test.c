#include "advanced_pointers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static int ptr_not_null(void *ptr, char* message) {
    bool verdict = ptr != NULL;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int ptr_not_equal(void *ptr1, void *ptr2, char* message) {
    bool verdict = ptr1 != ptr2;
    if (!verdict) {
        printf("Failure: %s\n", message);
    }
    return verdict;
}

static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

static int int_equal(int a, int b) { return (a - b) == 0; };

void test_allocate(void) {
    int *pointer = NULL;
    allocate_int(&pointer, 10);

    assert(ptr_not_null(pointer, "Should assing value to pointer"));
    assert(int_equal(*pointer, 10));
    free(pointer);
}

void test_does_not_overwrite(void) {
    int value = 5;
    int *pointer = &value;
    /* printf("pointer's value before: %p\n", pointer); */

    allocate_int(&pointer, 20);

    // pointer's value is changed by the function
    // since it will point to the allocated int now
    /* printf("pointer's value after: %p\n", pointer); */
    assert(int_equal(value, 5));
    assert(ptr_not_null(pointer, "Should assing value to pointer"));
    assert(int_equal(*pointer, 20));
    free(pointer);
}

void test_create_token_pointer_array_single(void) {
    token_t token = {"hello", 1, 1,};

    token_t **result = create_token_pointer_array(&token, 1);
    assert(ptr_not_null(result, "Result array should not be null"));
    assert(ptr_not_null(result[0], "First token pointer should not be null"));

    assert(string_equal(result[0]->literal, "hello"));
    assert(int_equal(result[0]->column, 1));
    assert(int_equal(result[0]->line, 1));
    assert(ptr_not_equal(&token, result[0], "Token pointer should not point to original token"));

    free(result[0]);
    free(result);
}

void test_create_token_pointer_array_multiple(void) {
    token_t tokens[3] = {
        {"foo", 1, 1},
        {"bar", 2, 5},
        {"baz", 3, 10},
    };
    token_t **result = create_token_pointer_array(tokens, 3);

    assert(result != NULL);
    for (int i=0; i < 3; i++) {
        assert(ptr_not_null(result[i], "Token pointer should not be null"));
        assert(string_equal(tokens[i].literal, result[i]->literal));
        assert(int_equal(tokens[i].column, result[i]->column));
        assert(int_equal(tokens[i].line, result[i]->line));
    }
    assert(ptr_not_equal(tokens, result[0], "Token pointer should not point to original token"));
    
    for (int i=0; i < 3; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    test_allocate();
    test_does_not_overwrite();
    test_create_token_pointer_array_single();
    test_create_token_pointer_array_multiple();
    printf("All tests passed.\n");
    return 0;
}
