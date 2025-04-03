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

bool array_set(object_t *object, size_t index, object_t *value) {
    if (object == NULL || value == NULL) {
        fprintf(stderr, "Error: NULL object or value passed to array_set().\n");
        return false;
    }

    if (object->kind != ARRAY) {
        fprintf(stderr, "Error: Tried to use array_set() on a non-array object.\n");
        return false;
    }

    if (object->data.v_array.size <= index) {
        fprintf(stderr, "Error: Index %zu out of bounds (array size: %zu).\n", index, object->data.v_array.size);
        return false;
    }

    object->data.v_array.elements[index] = value;

    return true;
};

object_t *array_get(object_t *object, size_t index) {
    if (object == NULL) {
        fprintf(stderr, "Error: NULL object passed to array_get().\n");
        return NULL;
    }

    if (object->kind != ARRAY) {
        fprintf(stderr, "Error: Tried to use array_get() on a non-array object.\n");
        return NULL;
    }

    if (object->data.v_array.size <= index) {
        fprintf(stderr, "Error: Index %zu out of bounds (array size: %zu).\n", index, object->data.v_array.size);
        return NULL;
    }

    return object->data.v_array.elements[index];
};

int print_length(object_t *object) {
    if (object == NULL) {
        return -1;
    }

    switch (object->kind) {
    case INTEGER:
        return 1;
        break;

    case FLOAT:
        return 1;
        break;

    case STRING:
        return strlen(object->data.v_string);
        break;

    case VECTOR3:
        return 3;
        break;

    case ARRAY:
        return object->data.v_array.size;
        break;

    default:
        return -1;
        break;
    }
}