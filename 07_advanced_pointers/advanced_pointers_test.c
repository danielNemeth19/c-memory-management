#include "advanced_pointers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

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

static int string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
};

static int float_equal(float a, float b) {
    const float epsilon = 1e-6f;
    return (a - b < epsilon) && (b - a < epsilon);
}

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
    token_t token = {
        "hello",
        1,
        1,
    };

    token_t **result = create_token_pointer_array(&token, 1);
    assert(ptr_not_null(result, "Result array should not be null"));
    assert(ptr_not_null(result[0], "First token pointer should not be null"));

    assert(string_equal(result[0]->literal, "hello"));
    assert(int_equal(result[0]->column, 1));
    assert(int_equal(result[0]->line, 1));
    assert(ptr_not_equal(&token, result[0],
                         "Token pointer should not point to original token"));

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
    for (int i = 0; i < 3; i++) {
        assert(ptr_not_null(result[i], "Token pointer should not be null"));
        assert(string_equal(tokens[i].literal, result[i]->literal));
        assert(int_equal(tokens[i].column, result[i]->column));
        assert(int_equal(tokens[i].line, result[i]->line));
    }
    assert(ptr_not_equal(tokens, result[0],
                         "Token pointer should not point to original token"));

    for (int i = 0; i < 3; i++) {
        free(result[i]);
    }
    free(result);
}

void test_snek_zero_out_int(void) {
    snek_int_t snek_int = {.name = "bal", .value = 10};
    snek_zero_out(&snek_int, INTEGER);
    assert(int_equal(snek_int.value, 0));
}

void test_snek_zero_out_float(void) {
    snek_float_t floaty;
    floaty.value = 21.12;
    snek_zero_out(&floaty, FLOAT);
    assert(float_equal(floaty.value, 0.0));
}

void test_snek_zero_out_bool(void) {
    snek_bool_t snek_bl = {.name = "bal", .value = 1};
    snek_zero_out(&snek_bl, BOOL);
    assert(int_equal(snek_bl.value, 0));
}

void test_snek_zero_out_nonzero_values(void) {
    snek_int_t snek_int;
    snek_float_t snek_float;
    snek_bool_t snek_bl;

    snek_int.value = -100;
    snek_float.value = -99.99;
    snek_bl.value = 255;

    snek_zero_out(&snek_int, INTEGER);
    snek_zero_out(&snek_float, FLOAT);
    snek_zero_out(&snek_bl, BOOL);

    assert(int_equal(snek_int.value, 0));
    assert(float_equal(snek_float.value, 0.0));
    assert(int_equal(snek_bl.value, 0));
}

void test_swap_ints(void) {
    int num_1 = 2;
    int num_2 = 4;
    int *ptr1 = &num_1;
    int *ptr2 = &num_2;

    swap_ints(ptr1, ptr2);
    assert(int_equal(num_1, 4));
    assert(int_equal(num_2, 2));
}

void test_swap_ints_same(void) {
    int num_1 = 10;
    swap_ints(&num_1, &num_1);
    assert(int_equal(num_1, 10));
}

void test_swap_chars(void) {
    char *text1 = "first";
    char *text2 = "second";
    char **ptr1 = &text1;
    char **ptr2 = &text2;

    swap_chars(ptr1, ptr2);
    assert(string_equal(text1, "second"));
    assert(string_equal(text2, "first"));
}

void test_swap_chars_longer(void) {
    char *text1 = "terminal.shop";
    char *text2 = "ssh";

    swap_chars(&text1, &text2);
    assert(string_equal(text1, "ssh"));
    assert(string_equal(text2, "terminal.shop"));
}

void test_generic_ints(void) {
    int i1 = 1234;
    int i2 = 5678;

    swap(&i1, &i2, sizeof(int));
    assert(int_equal(i1, 5678));
    assert(int_equal(i2, 1234));
}

void test_generic_string(void) {
    char *s1 = "first";
    char *s2 = "second";

    swap(&s1, &s2, sizeof(char *));
    assert(string_equal(s1, "second"));
    assert(string_equal(s2, "first"));
}

typedef struct CoffeShop {
    u_int16_t quality;
    u_int16_t taste;
    u_int16_t branding;
} coffe_shop_t;

void test_generic_structs(void) {
    coffe_shop_t sbucks = {2, 3, 4};
    coffe_shop_t terminalshop = {10, 10, 10};

    swap(&sbucks, &terminalshop, sizeof(coffe_shop_t));
    assert(int_equal(sbucks.quality, 10));
    assert(int_equal(sbucks.taste, 10));
    assert(int_equal(sbucks.branding, 10));

    assert(int_equal(terminalshop.quality, 2));
    assert(int_equal(terminalshop.taste, 3));
    assert(int_equal(terminalshop.branding, 4));
}

int main(void) {
    test_allocate();
    test_does_not_overwrite();
    test_create_token_pointer_array_single();
    test_create_token_pointer_array_multiple();
    test_snek_zero_out_int();
    test_snek_zero_out_float();
    test_snek_zero_out_bool();
    test_snek_zero_out_nonzero_values();
    test_swap_ints();
    test_swap_ints_same();
    test_swap_chars();
    test_swap_chars_longer();
    test_generic_ints();
    test_generic_structs();
    printf("All tests passed.\n");
    return 0;
}
