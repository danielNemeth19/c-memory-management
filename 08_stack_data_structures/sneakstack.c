#include "sneakstack.h"
#include <stdlib.h>

stack_t *stack_new(size_t capacity) {
    stack_t *s = malloc(sizeof(stack_t));
    if (s==NULL) {
        return NULL;
    }
    s->count = 0;
    s->capacity = capacity;
    s->data = malloc(capacity * sizeof(void));
    if (s->data == NULL) {
        return NULL;
    }
    return s;
}
