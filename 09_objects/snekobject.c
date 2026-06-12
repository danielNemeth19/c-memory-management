#include "snekobject.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *new_snek_string(char *value) {
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }
    int len = strlen(value) + 1;
    char *ptr = malloc(len * sizeof(char));
    if (ptr == NULL) {
        free(s_obj);
        return NULL;
    }
    strcpy(ptr, value);

    s_obj->kind = STRING;
    s_obj->data.v_string = ptr;
    return s_obj;
}

snek_object_t *new_snek_integer(int value) {
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = INTEGER;
    s_obj->data.v_int = value;
    return s_obj;
}

snek_object_t *new_snek_float(float value) {
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = FLOAT;
    s_obj->data.v_float = value;
    return s_obj;
}
