//
//  Chunk.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#include "Chunk.h"
#include <stdint.h>
#include <stdlib.h>


#define GROW_CAPACITY(capacity) \
((capacity) < 8) ? 8 : (capacity) * 2


void initChunk(Chunk *chunk) {
    chunk->code = NULL;
    chunk->count = 0;
    chunk->capacity = 0;
}

uint8_t *growArray(uint8_t *ptr, int size) {
    return realloc(ptr, size);
}

void writeChunk(Chunk *chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        chunk->capacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = growArray(chunk->code, chunk->capacity);
    }
    
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    free(chunk->code);
    initChunk(chunk);
}

void* reallocate(void *ptr, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(ptr);
        return NULL;
    }
    
    return realloc(ptr, newSize);
}

