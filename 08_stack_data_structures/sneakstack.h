#include <stddef.h>

typedef struct Stack {
    size_t count;
    size_t capacity;
    void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void stack_push(stack_t *stack, void *obj);
void *stack_pop(stack_t *stack);
void stack_free(stack_t *stack);
void scary_double_push(stack_t *s);
void stack_push_multiple_types(stack_t *s);
