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
