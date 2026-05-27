#include "advanced_pointers.h"
#include <stddef.h>
#include <stdlib.h>

void allocate_int(int **pointer_pointer, int value) {
    int *ptr = malloc(sizeof(int));
    *pointer_pointer = ptr;
    *ptr = value;
}

token_t **create_token_pointer_array(token_t *tokens, size_t count) {
    token_t **token_pointers = malloc(count * sizeof(token_t *));
    if (token_pointers == NULL) {
        exit(1);
    }
    for (size_t i = 0; i < count; ++i) {
        token_t *t_ptr = malloc(sizeof(token_t));
        t_ptr->column = tokens[i].column;
        t_ptr->line = tokens[i].line;
        t_ptr->literal = tokens[i].literal;
        token_pointers[i] = t_ptr;
    }
    return token_pointers;
}

void snek_zero_out(void *ptr, snek_object_kind_t kind) {
    if (kind == INTEGER) {
        ((snek_int_t *)ptr)->value = 0;
    } else if (kind == FLOAT) {
        ((snek_float_t *)ptr)->value = 0.0;
    } else {
        ((snek_bool_t *)ptr)->value = 0;
    }
}

void swap_ints(int *a, int *b) {
    /* printf("inside ptr1 before %d\n", *a); */
    /* printf("inside ptr2 before %d\n", *b); */
    int _t = *a;
    *a = *b;
    *b = _t;
    /* printf("inside ptr1 after %d\n", *a); */
    /* printf("inside ptr2 after %d\n", *b); */
}

void swap_ints_old(int *a, int *b) {
    // this function only swaps the values locally
    // i.e. in the function's stack frame
    // caller will see the same values
    int *_t = a;
    a = b;
    b = _t;
}

void swap_chars(char **a, char **b) {
    /* printf("inside ptr1 before %s\n", *a); */
    /* printf("inside ptr2 before %s\n", *b); */
    char *_t = *a;
    *a = *b;
    *b = _t;
    /* printf("inside ptr1 after %s\n", *a); */
    /* printf("inside ptr2 after %s\n", *b); */
}
