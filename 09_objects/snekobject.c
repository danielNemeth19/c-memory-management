#include "snekobject.h"
#include <stdlib.h>

snek_object_t *new_stack_integer(int value) {
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = INTEGER;
    s_obj->data.v_int = value;

    return s_obj;
}
