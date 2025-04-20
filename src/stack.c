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

void stack_push(stack_t *stack, void *object) {
    if (stack->count == stack->capacity) {
        fprintf(stderr, "Error: Attempted to push to a NULL stack pointer.\n");

        // Double stack capacity to avoid reallocing often
        stack->capacity *= 2;

        void **new_capacity = realloc(stack->data, stack->capacity * sizeof(void *));
        if (new_capacity == NULL) {
            stack->capacity /= 2;
            fprintf(stderr, "Error: Failed to reallocate memory during stack expansion to %zu elements.\n", new_capacity);
            exit(1);
        }
        stack->data = new_capacity;
    }

    stack->data[stack->count] = object;
    stack->count++;

    return;
}

void *stack_pop(stack_t *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Attempted to pop from a NULL stack pointer.\n");
        return NULL;
    }

    if (stack->count == 0) {
        fprintf(stderr, "Warning: Stack underflow! Tried to pop from an empty stack.\n");
        return NULL;
    }
    stack->count--;

    printf("Popped element at index %zu: %p\n", stack->count, stack->data[stack->count]);
    return stack->data[stack->count];
}

void stack_free(stack_t *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Warning: Tried to free a NULL stack pointer. (Stack is empty)\n");
        return;
    }

    if (stack->data != NULL) {
        fprintf(stderr, "[stack_free] Freeing stack data with %zu elements.\n", stack->count);
        free(stack->data);
    }
    free(stack);
}