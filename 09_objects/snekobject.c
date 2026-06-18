#include "snekobject.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    snek_object_t *new_obj = malloc(sizeof(snek_object_t));
    if (a->kind == INTEGER) {
        if (b->kind == INTEGER) {
            new_obj->kind = INTEGER;
            new_obj->data.v_int = a->data.v_int + b->data.v_int;
            return new_obj;
        }
        if (b->kind == FLOAT) {
            new_obj->kind = FLOAT;
            new_obj->data.v_float = (float)a->data.v_int + b->data.v_float;
            return new_obj;
        }
        free(new_obj);
        return NULL; 
    }
    if (a->kind == FLOAT) {
        new_obj->kind = FLOAT;
        if (b->kind == INTEGER) {
            new_obj->data.v_float = a->data.v_float + (float)b->data.v_int;
            return new_obj;
        }
        if (b->kind == FLOAT) {
            new_obj->data.v_float = a->data.v_float + b->data.v_float;
            return new_obj;
        }
        free(new_obj);
        return NULL;
    }
}

int snek_length(snek_object_t *obj) {
    if (obj == NULL) {
        return -1;
    }
    switch (obj->kind) {
    case INTEGER:
        return 1;
    case FLOAT:
        return 1;
    case STRING:
        return strlen(obj->data.v_string);
    case VECTOR3:
        return 3;
    case ARRAY:
        return obj->data.v_array.size;
    default:
        return -1;
    }
}

snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
    if (array == NULL || array->kind != ARRAY) {
        return NULL;
    }
    if (array->data.v_array.size <= index) {
        return NULL;
    }
    snek_object_t *elem = array->data.v_array.elements[index];
    return elem;
}

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
    if (array == NULL || value == NULL) {
        return false;
    }
    if (array->kind != ARRAY) {
        return false;
    }
    if (array->data.v_array.size <= index) {
        return false;
    }
    array->data.v_array.elements[index] = value;
    return true;
}

snek_object_t *new_snek_array(size_t size) {
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
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

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
    if ((x == NULL) || (y == NULL) || (z == NULL)) {
        return NULL;
    }
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }

    s_obj->kind = VECTOR3;
    s_obj->data.v_vector3.x = x;
    s_obj->data.v_vector3.y = y;
    s_obj->data.v_vector3.z = z;
    return s_obj;
}

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
