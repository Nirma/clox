//
//  Value.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/24.
//

#include "Value.h"
#include "Chunk.h"

void initValueArray(ValueArray* array) {
    array->count = 0;
    array->values = NULL;
    array->capacity = 0;
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        size_t oldsize = array->capacity;
        array->capacity = GROW_CAPACITY(array->capacity);
        array->values = reallocate(array->values, oldsize, array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    free(array->values);
    initValueArray(array);
}
