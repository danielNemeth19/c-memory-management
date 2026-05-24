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
    for (size_t i=0; i < count; ++i) {
        token_t *t_ptr = malloc(sizeof(token_t));
        t_ptr->column = tokens[i].column;
        t_ptr->line = tokens[i].line;
        t_ptr->literal = tokens[i].literal;
        token_pointers[i] = t_ptr;
    }
    return token_pointers;
}
