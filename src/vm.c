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
