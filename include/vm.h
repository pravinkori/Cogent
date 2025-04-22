#include "stack.h"

typedef struct VirtualMachine {
    stack_t *frames;
    stack_t *objects;
} vm_t;

vm_t *vm_new();