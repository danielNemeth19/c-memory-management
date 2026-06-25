#include "snekobject.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static snek_object_t *_snek_add_int_to_number(int a_int, snek_object_t *b) {
    switch (b->kind) {
    case INTEGER: {
        int sum = a_int + b->data.v_int;
        return new_snek_integer(sum);
    }
    case FLOAT: {
        float sum = (float)a_int + b->data.v_float;
        return new_snek_float(sum);
    }
    default:
        return NULL;
    }
}

static snek_object_t *_snek_add_float_to_number(float a_flt, snek_object_t *b) {
    switch (b->kind) {
    case INTEGER: {
        float sum = a_flt + (float)b->data.v_int;
        return new_snek_float(sum);
    }
    case FLOAT: {
        float sum = a_flt + b->data.v_float;
        return new_snek_float(sum);
    }
    default:
        return NULL;
    }
}

static snek_object_t *_snek_add_str(snek_object_t *a, snek_object_t *b) {
    switch (b->kind) {
    case STRING: {
        size_t t_len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
        char *interim = calloc(t_len, sizeof(char));
        if (interim == NULL) {
            return NULL;
        }
        strcat(interim, a->data.v_string);
        strcat(interim, b->data.v_string);
        snek_object_t *new_obj = new_snek_string(interim);
        free(interim);
        return new_obj;
    }
    default:
        return NULL;
    }
}

static snek_object_t *_snek_add_vector3(snek_object_t *a, snek_object_t *b) {
    switch (b->kind) {
    case VECTOR3: {
        snek_object_t *vx = snek_add(a->data.v_vector3.x, b->data.v_vector3.x);
        snek_object_t *vy = snek_add(a->data.v_vector3.y, b->data.v_vector3.y);
        snek_object_t *vz = snek_add(a->data.v_vector3.z, b->data.v_vector3.z);
        if (vx == NULL || vy == NULL || vz == NULL) {
            free(vx);
            free(vy);
            free(vz);
            return NULL;
        }
        snek_object_t *new_obj = new_snek_vector3(vx, vy, vz);
        if (new_obj == NULL) {
            free(vx);
            free(vy);
            free(vz);
            return NULL;
        }
        return new_obj;
    }
    default:
        return NULL;
    }
}

static snek_object_t *_snek_add_array(snek_object_t *a, snek_object_t *b) {
    switch (b->kind) {
    case ARRAY: {
        size_t len = a->data.v_array.size + b->data.v_array.size;
        snek_object_t *new_obj_array = new_snek_array(len);
        if (new_obj_array == NULL) {
            return NULL;
        }
        for (size_t i = 0; i < a->data.v_array.size; i++) {
            snek_object_t *item = snek_array_get(a, i);
            snek_array_set(new_obj_array, i, item);
        }
        size_t b_index = a->data.v_array.size;
        for (size_t y = 0; y < b->data.v_array.size; y++) {
            snek_object_t *item = snek_array_get(b, y);
            snek_array_set(new_obj_array, b_index + y, item);
        }
        return new_obj_array;
    }
    default:
        return NULL;
    }
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    switch (a->kind) {
    case INTEGER:
        return _snek_add_int_to_number(a->data.v_int, b);
    case FLOAT:
        return _snek_add_float_to_number(a->data.v_float, b);
    case STRING:
        return _snek_add_str(a, b);
    case VECTOR3:
        return _snek_add_vector3(a, b);
    case ARRAY:
        return _snek_add_array(a, b);
    }
    return NULL;
}

snek_object_t *snek_add_old(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (a->kind == INTEGER) {
        if (b->kind == INTEGER) {
            int sum = a->data.v_int + b->data.v_int;
            snek_object_t *new_obj = new_snek_integer(sum);
            return new_obj;
        }
        if (b->kind == FLOAT) {
            float sum = a->data.v_int + b->data.v_float;
            snek_object_t *new_obj = new_snek_float(sum);
            return new_obj;
        }
        return NULL;
    }
    if (a->kind == FLOAT) {
        if (b->kind == INTEGER) {
            float sum = a->data.v_float + (float)b->data.v_int;
            snek_object_t *new_obj = new_snek_float(sum);
            return new_obj;
        }
        if (b->kind == FLOAT) {
            float sum = a->data.v_float + b->data.v_float;
            snek_object_t *new_obj = new_snek_float(sum);
            return new_obj;
        }
        return NULL;
    }
    if (a->kind == STRING) {
        if (b->kind != STRING) {
            return NULL;
        }
        size_t t_len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
        char *interim = calloc(t_len, sizeof(char));
        if (interim == NULL) {
            return NULL;
        }
        strcat(interim, a->data.v_string);
        strcat(interim, b->data.v_string);
        snek_object_t *res = new_snek_string(interim);
        free(interim);
        return res;
    }
    if (a->kind == VECTOR3) {
        if (b->kind != VECTOR3) {
            return NULL;
        }
        snek_object_t *vx = snek_add(a->data.v_vector3.x, b->data.v_vector3.x);
        snek_object_t *vy = snek_add(a->data.v_vector3.y, b->data.v_vector3.y);
        snek_object_t *vz = snek_add(a->data.v_vector3.z, b->data.v_vector3.z);
        if (vx == NULL || vy == NULL || vz == NULL) {
            free(vx);
            free(vy);
            free(vz);
            return NULL;
        }
        snek_object_t *new_obj = new_snek_vector3(vx, vy, vz);
        if (new_obj == NULL) {
            free(vx);
            free(vy);
            free(vz);
            return NULL;
        }
        return new_obj;
    }
    if (a->kind == ARRAY) {
        if (b->kind != ARRAY) {
            return NULL;
        }
        size_t len = a->data.v_array.size + b->data.v_array.size;
        snek_object_t *new_obj_array = new_snek_array(len);
        if (new_obj_array == NULL) {
            return NULL;
        }
        for (size_t i = 0; i < a->data.v_array.size; i++) {
            snek_object_t *curr_arr = snek_array_get(a, i);
            bool store = snek_array_set(new_obj_array, i, curr_arr);
        }
        size_t b_index = a->data.v_array.size;
        for (size_t y = 0; y < b->data.v_array.size; y++) {
            snek_object_t *curr_arr = snek_array_get(b, y);
            snek_array_set(new_obj_array, b_index + y, curr_arr);
        }
        return new_obj_array;
    }
    return NULL;
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
    if (value == NULL) {
        return NULL;
    }
    snek_object_t *s_obj = malloc(sizeof(snek_object_t));
    if (s_obj == NULL) {
        return NULL;
    }
    size_t len = strlen(value) + 1;
    char *ptr = malloc(len);
    if (ptr == NULL) {
        free(s_obj);
        return NULL;
    }
    /* strcpy(ptr, value); */
    /* memcpy is equivalent for this use case: */
    memcpy(ptr, value, len);

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
