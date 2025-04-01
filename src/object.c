#include "../include/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

object_t *new_integer(int value) {
    object_t *int_obj = malloc(sizeof(object_t));

    if (int_obj == NULL) {
        printf("Memory Allocation for integer object failed");
        return NULL;
    }

    int_obj->kind = INTEGER;
    int_obj->data.v_int = value;

    return int_obj;
}

object_t *new_float(float value) {
    object_t *float_obj = malloc(sizeof(object_t));

    if (float_obj == NULL) {
        printf("Memory Allocation for float object failed");
        return NULL;
    }

    float_obj->kind = FLOAT;
    float_obj->data.v_float = value;

    return float_obj;
}

object_t *new_string(char *value) {
    object_t *string_obj = malloc(sizeof(object_t));

    if (string_obj == NULL) {
        printf("Memory Allocation for float object failed\n");
        return NULL;
    }

    int input_length = strlen(value);
    char *string_copy = malloc(input_length + 1);
    if (string_copy == NULL) {
        printf("Memory allocation failed for string copy!\n");
        free(string_obj);
        printf("Memory freed successfully!\n");
        return NULL;
    }

    strcpy(string_copy, value);

    string_obj->kind = STRING;
    string_obj->data.v_string = string_copy;

    return string_obj;
}

object_t *new_vector(object_t *x, object_t *y, object_t *z) {
    if (x == NULL || y == NULL || z == NULL) {
        printf("Error: One or more vector components are NULL!\n");
        return NULL;
    }

    object_t *vector_obj = malloc(sizeof(object_t));
    if (vector_obj == NULL) {
        printf("Memory allocation for vector failed\n");
        return NULL;
    }

    vector_obj->kind = VECTOR3;
    vector_obj->data.v_vector3 = (vector_t){.x = x, .y = y, .z = z};

    printf("Vector created successfully: [%p, %p, %p]\n", x, y, z);

    return vector_obj;
}

object_t *new_array(size_t size) {
    object_t *array_obj = malloc(sizeof(object_t));

    if (array_obj == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for object_t (array).\n");
        return NULL;
    }

    object_t **elements = calloc(size, sizeof(object_t *));
    if (elements == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for array elements (size=%zu).\n", size);
        free(array_obj);
        return NULL;
    }

    array_obj->kind = ARRAY;

    array_t array = {.size = size, .elements = elements};
    array_obj->data.v_array = array;

    return array_obj;
}
