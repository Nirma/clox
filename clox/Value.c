//
//  Value.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/24.
//

#include "Value.h"
#include "Chunk.h"
#include "Debug.h"
#include "VM.h"

void initValueArray(ValueArray* array) {
    array->count = 0;
    array->values = NULL;
    array->capacity = 0;
}

void writeValueArray(ValueArray* array, Value value) {
    
    if (array->capacity < array->count + 1) {
        array->capacity = GROW_CAPACITY(array->capacity);
        array->values = realloc(array->values, array->capacity * sizeof(Value));
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    free(array->values);
    initValueArray(array);
}
