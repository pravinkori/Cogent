#include <stdio.h>
#include <stdlib.h>
#include "../include/object.h"

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
