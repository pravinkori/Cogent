#include <stdio.h>

#include "../include/stack.h"

stack_t *stack_new(size_t capcity) {
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capcity;

    stack->data = malloc(stack->capacity * sizeof(void *));
    if (stack->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for data.\n");
        return NULL;
    }

    return stack;
}
