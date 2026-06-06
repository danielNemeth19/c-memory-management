#include "sneakstack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_push_multiple_types(stack_t *s) {
    float *n_ptr = malloc(sizeof(float));
    *n_ptr = 3.14;
    stack_push(s, n_ptr);
    const char *mystr = "Sneklang is blazingly slow!";
    int length = strlen(mystr) + 1;
    char *str_ptr = malloc(length * sizeof(char));
    memcpy(str_ptr, mystr, length);
    stack_push(s, str_ptr);
}

void scary_double_push(stack_t *s) {
    int n = 1337;
    // here we say: "pretend the number 1337 is a pointer"
    // but 1337 is not an address to an int
    void *ptr = (void *)(intptr_t)n;
    stack_push(s, ptr);
    int *n_ptr = malloc(sizeof(int));
    *n_ptr = 1024;
    stack_push(s, n_ptr);
}

void stack_free(stack_t *stack) {
    if (stack == NULL) {
        return;
    }
    if (stack->data != NULL) {
        free(stack->data);
    }
    free(stack);
}

void *stack_pop(stack_t *stack) {
    if (stack->count == 0) {
        return NULL;
    }
    /* stack->count -= 1 ; */
    stack->count--;
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
