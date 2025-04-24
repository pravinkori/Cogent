#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/object.h"

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
        free(object);
        break;
    }
    case ARRAY: {
        array_t arr = object->data.v_array;
        for (int i = 0; i < arr.size; i++) {
            refcount_dec(arr.elements[i]);
        }

        free(object->data.v_array.elements);
        free(object);
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