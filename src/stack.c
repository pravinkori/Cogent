#include <stdio.h>

#include "../include/stack.h"

stack_t *stack_new(size_t capacity) {
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capacity;

    stack->data = malloc(stack->capacity * sizeof(void *));
    if (stack->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for data.\n");
        free(stack);
        return NULL;
    }

    return stack;
}
