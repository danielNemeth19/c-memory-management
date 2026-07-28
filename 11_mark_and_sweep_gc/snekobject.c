#include "snekobject.h"
#include <assert.h>

void snek_object_free(snek_object_t *obj) {
    switch (obj->kind) {
    case INTEGER: {
        break;
    }
    case FLOAT: {
        break;
    }
    case STRING: {
        free(obj->data.v_string);
        break;
    }
    case VECTOR3: {
        break;
    }
    case ARRAY: {
        free(obj->data.v_array.elements);
        break;
    }
    default:
        assert(false);
    }
    free(obj);
}

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
    if (array == NULL || value == NULL) {
        return false;
    }
    if (array->kind != ARRAY) {
        return false;
    }
    if (index >= array->data.v_array.size) {
        return false;
    }
    // No need to change refcounts, we will find the garbage values
    // later through mark-and-sweep.

    // Setting value directly (already checked size constraint)
    array->data.v_array.elements[index] = value;
    return true;

}
