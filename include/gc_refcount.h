#pragma once

#include "object.h"

void refcount_inc(object_t *object);
void refcount_dec(object_t *object);
void refcount_free(object_t *object);
