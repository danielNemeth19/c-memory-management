#include "sneakstack.h"
#include <stdlib.h>

void stack_push(stack_t *stack, void *obj) {
    if (stack->count == stack->capacity) {
        void *new_data = realloc(stack->data, 2 * stack->capacity * sizeof(void *));
        if (new_data == NULL) {
            free(new_data);
            return;
        };
        stack->data = new_data;
        stack->capacity = 2 * stack->capacity;
    };
    if (stack->count < stack->capacity) {
        stack->data[stack->count] = obj;
    }
    stack->count++;
}

stack_t *stack_new(size_t capacity) {
    stack_t *s = malloc(sizeof(stack_t));
    if (s == NULL) {
        return NULL;
    }
    s->count = 0;
    s->capacity = capacity;
    s->data = malloc(s->capacity * sizeof(void *));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    return s;
}
