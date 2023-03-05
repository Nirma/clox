//
//  Chunk.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#include "Chunk.h"
#include <stdint.h>
#include <stdlib.h>
#include "Debug.h"


void initChunk(Chunk *chunk) {
    chunk->code = NULL;
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->values);
}

int addValue(Chunk *chunk, Value value) {
    ValueArray *array = &chunk->values;
    if (array->capacity < array->count + 1) {
        array->capacity = GROW_CAPACITY(array->capacity);
        array->values = realloc(array->values, array->capacity);
        printf("Allocating...");
    }

    array->values[array->count] = value;
    array->count++;
   // writeValueArray(&chunk->values, value);
    return chunk->values.count - 1;
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        chunk->capacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = realloc(chunk->code, chunk->capacity);
        chunk->lines = realloc(chunk->lines, chunk->capacity);
    }
    
    chunk->lines[chunk->count] = line;
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    free(chunk->code);
    freeValueArray(&chunk->values);
    initChunk(chunk);
    
}
