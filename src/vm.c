#include <stdio.h>

#include "../include/vm.h"

vm_t *vm_new() {
    vm_t *vm = malloc(sizeof(vm_t));

    if (vm == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    vm->frames = stack_new(8);
    if (vm->frames == NULL) {
        free(vm);
        return NULL;
    }

    vm->objects = stack_new(8);
    if (vm->objects == NULL) {
        free(vm);
        return NULL;
    }

    return vm;
}

void vm_free(vm_t *vm) {
    if (vm == NULL) {
        return;
    }

    for (int i = 0; i < vm->frames->count; i++) {
        frame_free(vm->frames->data[i]);
    }

    stack_free(vm->frames);
    stack_free(vm->objects);

    free(vm);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
    if (vm == NULL || frame == NULL) {
        fprintf(stderr, "Warning: vm_frame_push received NULL vm or frame.\n");
        return;
    }

    stack_push(vm->frames, (void *)frame);
    fprintf(stdout, "Frame pushed: %p\n", (void *)frame);
}

frame_t *vm_new_frame(vm_t *vm) {
    frame_t *frame = malloc(sizeof(frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->references = stack_new(8);
    if (frame->references == NULL) {
        free(frame);
        return NULL;
    }

    vm_frame_push(vm, frame);
    return frame;
}

void frame_free(frame_t *frame) {
    if (frame == NULL) {
        return;
    }

    stack_free(frame->references);
    free(frame);
}