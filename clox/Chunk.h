//
//  Chunk.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#ifndef Chunk_h
#define Chunk_h

#include <stdint.h>
#include "Value.h"

#define GROW_CAPACITY(capacity) \
((capacity) < 8) ? 8 : (capacity) * 2

typedef enum {
    OP_RETURN,
    OP_CONST,
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULT,
    OP_DIVIDE
} OpCode;

typedef struct {
    ValueArray values;
    uint8_t *code;
    int *lines;
    int capacity;
    int count;
} Chunk;

void initChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte, int line);

void freeChunk(Chunk *chunk);

int addValue(Chunk *chunk, Value value);

void* reallocate(void *ptr, size_t oldSize, size_t newSize);

#endif /* Chunk_h */
