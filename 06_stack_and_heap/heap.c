#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

// variable with unknown size at compile time
// should be allocated on the heap
// full_greeting -> is a pointer variable that lives on the stack (&full_greeting is an address on stack)
// full_greeting holds the address of memory allocated on the heap by malloc
// the data for the greeting is stored in this heap memory
char *get_full_greeting(char *greeting, char *name, int size) {
    char *full_greeting = malloc(size * sizeof(char));
    snprintf(full_greeting, size, "%s %s", greeting, name);
    return full_greeting;
}
