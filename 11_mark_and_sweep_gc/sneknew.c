#include "sneknew.h"
#include "snekobject.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *_new_snek_object(vm_t *vm) {
    snek_object_t *obj = calloc(1, sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }
    obj->is_marked = false;
    vm_track_object(vm, obj);
    return obj;
}

snek_object_t *new_snek_array(vm_t *vm, size_t size) {
    snek_object_t *s_obj = _new_snek_object(vm);
    if (s_obj == NULL) {
        return NULL;
    }
    snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
    if (elements == NULL) {
        free(s_obj);
        return NULL;
    }
    s_obj->kind = ARRAY;

    snek_array_t s_arr = {.size = size, .elements = elements};

    s_obj->data.v_array = s_arr;
    return s_obj;
}

snek_object_t *new_snek_vector3(vm_t *vm, snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
    if ((x == NULL) || (y == NULL) || (z == NULL)) {
        return NULL;
    }
    snek_object_t *s_obj = _new_snek_object(vm);
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = VECTOR3;
    s_obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
    return s_obj;
}

snek_object_t *new_snek_integer(vm_t *vm, int value) {
    snek_object_t *s_obj = _new_snek_object(vm);
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = INTEGER;
    s_obj->data.v_int = value;
    return s_obj;
}

snek_object_t *new_snek_float(vm_t *vm, float value) {
    snek_object_t *s_obj = _new_snek_object(vm);
    if (s_obj == NULL) {
        return NULL;
    }
    s_obj->kind = FLOAT;
    s_obj->data.v_float = value;
    return s_obj;
}

snek_object_t *new_snek_string(vm_t *vm, char *value) {
    if (value == NULL) {
        return NULL;
    }
    snek_object_t *s_obj = _new_snek_object(vm);
    if (s_obj == NULL) {
        return NULL;
    }
    size_t len = strlen(value);
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        free(s_obj);
        return NULL;
    }
    strcpy(dst, value);
    /* memcpy is equivalent for this use case: */
    /* memcpy(dst, value, len); */

    s_obj->kind = STRING;
    s_obj->data.v_string = dst;
    return s_obj;
}
