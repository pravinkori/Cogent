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