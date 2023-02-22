//
//  Chunk.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#ifndef Chunk_h
#define Chunk_h

#include <stdint.h>

typedef enum {
    OP_RETURN
} OpCode;

typedef struct {
    uint8_t *code;
    int capacity;
    int count;
} Chunk;

void initChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte);

void freeChunk(Chunk *chunk);

void* reallocate(void *ptr, size_t oldSize, size_t newSize);


#endif /* Chunk_h */
