#ifndef VM_H
#define VM_H

#include "vm.h"
#include "snekobject.h"
#include <stdbool.h>
#include <stdio.h>

void sweep(vm_t *vm) {
    for (size_t i = 0; i < vm->objects->count; i++) {
        snek_object_t *obj = vm->objects->data[i];
        if (obj->is_marked) {
            obj->is_marked = false;
        } else {
            snek_object_free(obj);
            vm->objects->data[i] = NULL;
        }
    }
    stack_remove_nulls(vm->objects);
}

void vm_collect_garbage(vm_t *vm) {
    mark(vm);
    trace(vm);
    sweep(vm);
}

void mark(vm_t *vm) {
    stack_t *frames = vm->frames;
    for (int i = 0; i < frames->count; i++) {
        frame_t *frame = frames->data[i];
        stack_t *references = frame->references;
        for (int y = 0; y < references->count; y++) {
            snek_object_t *obj = references->data[y];
            obj->is_marked = true;
        }
    }
}

void trace(vm_t *vm) {
    stack_t *gray_objects = stack_new(8);
    if (gray_objects == NULL) {
        return;
    }
    stack_t *objects = vm->objects;
    for (int i = 0; i < objects->count; i++) {
        snek_object_t *obj = objects->data[i];
        if (obj->is_marked) {
            stack_push(gray_objects, obj);
        }
    }
    while (gray_objects->count > 0) {
        void *item = stack_pop(gray_objects);
        trace_blacken_object(gray_objects, item);
    }
    stack_free(gray_objects);
}

void trace_blacken_object(stack_t *gray_objects, snek_object_t *ref) {
    switch (ref->kind) {
    case INTEGER: {
        return;
    }
    case FLOAT: {
        return;
    }
    case STRING: {
        return;
    }
    case VECTOR3: {
        if (ref->data.v_vector3.x) {
            trace_mark_object(gray_objects, ref->data.v_vector3.x);
        }
        if (ref->data.v_vector3.y) {
            trace_mark_object(gray_objects, ref->data.v_vector3.y);
        }
        if (ref->data.v_vector3.z) {
            trace_mark_object(gray_objects, ref->data.v_vector3.z);
        }
        return;
    }
    case ARRAY: {
        for (size_t i = 0; i < ref->data.v_array.size; i++) {
            trace_mark_object(gray_objects, ref->data.v_array.elements[i]);
        }
    }
    default:
        return;
    }
}

void trace_mark_object(stack_t *gray_objects, snek_object_t *ref) {
    if (ref == NULL || ref->is_marked) {
        return;
    }
    ref->is_marked = true;
    stack_push(gray_objects, ref);
}

void frame_reference_object(frame_t *frame, snek_object_t *obj) {
    stack_push(frame->references, obj);
}

vm_t *vm_new() {
    vm_t *vm = malloc(sizeof(vm_t));
    if (vm == NULL) {
        return NULL;
    }
    vm->frames = stack_new(8);
    vm->objects = stack_new(8);
    return vm;
}

void vm_free(vm_t *vm) {
    stack_t *frames = vm->frames;
    for (int i = 0; i < frames->count; i++) {
        frame_t *f = frames->data[i];
        frame_free(f);
    }
    stack_free(vm->frames);
    stack_t *objects = vm->objects;
    for (int i = 0; i < objects->count; i++) {
        snek_object_t *obj = objects->data[i];
        snek_object_free(obj);
    }
    stack_free(vm->objects);
    free(vm);
}

void vm_track_object(vm_t *vm, snek_object_t *obj) {
    if (obj == NULL) {
        return;
    }
    stack_push(vm->objects, obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) { stack_push(vm->frames, frame); }

frame_t *vm_frame_pop(vm_t *vm) {
    return stack_pop(vm->frames);
}

frame_t *vm_new_frame(vm_t *vm) {
    frame_t *frame = malloc(sizeof(frame_t));
    if (frame == NULL) {
        return NULL;
    }
    frame->references = stack_new(8);
    vm_frame_push(vm, frame);
    return frame;
}

void frame_free(frame_t *frame) {
    stack_free(frame->references);
    free(frame);
}

#endif // VM_H
