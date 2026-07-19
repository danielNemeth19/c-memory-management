#ifndef VM_H
#define VM_H

#include "vm.h"
#include "snekobject.h"
#include <stdlib.h>

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
    stack_free(vm->frames);
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
