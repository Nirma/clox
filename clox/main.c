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
    location = addValue(&chunk, 123);
    writeChunk(&chunk, OP_CONST, 5);
    writeChunk(&chunk, location, 1);
    
    
    location = addValue(&chunk, 37);
    writeChunk(&chunk, OP_CONST, 7);
    writeChunk(&chunk, location, 150);
    
    writeChunk(&chunk, OP_ADD, 1);
    writeChunk(&chunk, OP_NEGATE, 1);
    
    location = addValue(&chunk, 500);
   // writeChunk(&chunk, OP_CONST, 1);
   // writeChunk(&chunk, location, 150);
    
    

    interpretChunk(&chunk);
    return 0;
}
