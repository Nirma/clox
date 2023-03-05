//
//  main.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#include "VM.h"
#include <stdio.h>
#include "Chunk.h"
#include "Debug.h"

#define DEBUG 1

int main(int argc, const char * argv[]) {
    Chunk chunk;
    
    initVM();
    initChunk(&chunk);
    int location;
    location = addValue(&chunk, 50);
    writeChunk(&chunk, OP_CONST, 123);
    writeChunk(&chunk, location, 123);
    
    
    location = addValue(&chunk, 150);
    writeChunk(&chunk, OP_CONST, 123);
    writeChunk(&chunk, location, 123);
    
    writeChunk(&chunk, OP_ADD, 123);
    
    location = addValue(&chunk, 2);
    writeChunk(&chunk, OP_CONST, 1);
    writeChunk(&chunk, location, 150);
    
    writeChunk(&chunk, OP_MULT, 2);
    location = addValue(&chunk, 2);
    writeChunk(&chunk, OP_CONST, 1);
    writeChunk(&chunk, location, 150);
    
    writeChunk(&chunk, OP_MULT, 2);
    
    writeChunk(&chunk, OP_RETURN, 1);
    
    interpretChunk(&chunk);
    return 0;
}
