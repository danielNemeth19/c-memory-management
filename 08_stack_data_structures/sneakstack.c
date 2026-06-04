#include "sneakstack.h"
#include <stdlib.h>

void *stack_pop(stack_t *stack){
    if (stack->count == 0) {
        return NULL;
    }
    stack->count -= 1 ;
    return stack->data[stack->count];
}

void stack_push(stack_t *stack, void *obj) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        void *temp = realloc(stack->data, stack->capacity * sizeof(void *));
        if (temp == NULL) {
            stack->capacity /= 2;
            return;
        };
        stack->data = temp;
    };
    stack->data[stack->count] = obj;
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
