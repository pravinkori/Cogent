#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/object.h"
#include "assert.h"

void refcount_dec(object_t *object) {
    if (object == NULL) {
        return;
    }

    object->ref_count--;
    if (object->ref_count == 0) {
        refcount_free(object);
    }

    return;
}

void refcount_free(object_t *object) {
    if (object == NULL) {
        return;
    }

    switch (object->kind) {
    case INTEGER: {
        free(object);
        break;
    }
    case FLOAT: {
        free(object);
        break;
    }
    case STRING: {
        free(object->data.v_string);
        free(object);
        break;
    }
    case VECTOR3: {
        vector_t vec = object->data.v_vector3;
        refcount_dec(vec.x);
        refcount_dec(vec.y);
        refcount_dec(vec.z);
        break;
    }
    case ARRAY: {
        array_t arr = object->data.v_array;
        for (int i = 0; i < arr.size; i++) {
            refcount_dec(arr.elements[i]);
        }

        free(object->data.v_array.elements);
        break;
    }

    default:
        assert(false);
        break;
    }
}

void refcount_inc(object_t *object) {
    if (object == NULL) {
        return;
    }

    object->ref_count++;
    return;
}

object_t *_new_object() {
    object_t *object = calloc(1, sizeof(object_t));
    if (object == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for object.\n");
        return NULL;
    }

    object->ref_count = 1;

    return object;
}

object_t *new_integer(int value) {
    // object_t *int_obj = malloc(sizeof(object_t));
    object_t *int_obj = _new_object();

    if (int_obj == NULL) {
        printf("Memory Allocation for integer object failed");
        return NULL;
    }

    int_obj->kind = INTEGER;
    int_obj->data.v_int = value;

    return int_obj;
}

object_t *new_float(float value) {
    // object_t *float_obj = malloc(sizeof(object_t));
    object_t *float_obj = _new_object();

    if (float_obj == NULL) {
        printf("Memory Allocation for float object failed");
        return NULL;
    }

    float_obj->kind = FLOAT;
    float_obj->data.v_float = value;

    return float_obj;
}

object_t *new_string(char *value) {
    // object_t *string_obj = malloc(sizeof(object_t));
    object_t *string_obj = _new_object();

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

    // object_t *vector_obj = malloc(sizeof(object_t));
    object_t *vector_obj = _new_object();
    if (vector_obj == NULL) {
        printf("Memory allocation for vector failed\n");
        return NULL;
    }

    vector_obj->kind = VECTOR3;

    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);
    vector_obj->data.v_vector3 = (vector_t){.x = x, .y = y, .z = z};

    printf("Vector created successfully: [%p, %p, %p]\n", x, y, z);

    return vector_obj;
}

object_t *new_array(size_t size) {
    // object_t *array_obj = malloc(sizeof(object_t));
    object_t *array_obj = _new_object();

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

    refcount_inc(value);
    if (object->data.v_array.elements[index] != NULL) {
        refcount_dec(object->data.v_array.elements[index]);
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

object_t *object_add(object_t *lhs, object_t *rhs) {
    if (lhs == NULL || rhs == NULL) {
        return NULL;
    }

    switch (lhs->kind) {
    case INTEGER: {
        switch (rhs->kind) {
        case INTEGER:
            return new_integer(lhs->data.v_int + rhs->data.v_int);
            break;
        case FLOAT:
            return new_float((float)lhs->data.v_int + rhs->data.v_float);
            break;
        default:
            return NULL;
            break;
        }
    }

    case FLOAT: {
        switch (rhs->kind) {
        case INTEGER:
            return new_float(lhs->data.v_float + (float)rhs->data.v_int);
            break;
        case FLOAT:
            return new_float(lhs->data.v_float + rhs->data.v_float);
            break;
        default:
            return NULL;
            break;
        }
    }

    case STRING: {
        if (rhs->kind != STRING) {
            return NULL;
        }
        size_t length = strlen(lhs->data.v_string) + strlen(rhs->data.v_string) + 1;

        char *concat_string = calloc(sizeof(char *), length);
        if (concat_string == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for concatinated string.\n");
            return NULL;
        }

        strcat(concat_string, lhs->data.v_string);
        strcat(concat_string, rhs->data.v_string);

        object_t *result_str = new_string(concat_string);

        free(concat_string);

        return result_str;
    }

    case VECTOR3: {
        if (rhs->kind != VECTOR3) {
            return NULL;
        }

        object_t *x = object_add(lhs->data.v_vector3.x, rhs->data.v_vector3.x);
        object_t *y = object_add(lhs->data.v_vector3.y, rhs->data.v_vector3.y);
        object_t *z = object_add(lhs->data.v_vector3.z, rhs->data.v_vector3.z);

        return new_vector(x, y, z);
    }

    case ARRAY: {
        if (rhs->kind != ARRAY) {
            return NULL;
        }

        size_t total_size = lhs->data.v_array.size + rhs->data.v_array.size;

        object_t *result_arr = new_array(total_size);

        for (size_t i = 0; i < lhs->data.v_array.size; i++) {
            array_set(
                result_arr,
                i,
                array_get(lhs, i));
        }

        for (size_t i = 0; i < rhs->data.v_array.size; i++) {
            array_set(
                result_arr,
                i + lhs->data.v_array.size,
                array_get(rhs, i));
        }

        return result_arr;
    }

    default:
        return NULL;
        break;
    }
}
