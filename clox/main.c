//
//  main.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#include <stdio.h>
#include "Chunk.h"
#include "Debug.h"

int main(int argc, const char * argv[]) {
    Chunk chunk;
    

    initChunk(&chunk);
    writeChunk(&chunk, OP_CONST);
    int location = addValue(&chunk, 123);
    writeChunk(&chunk, location);
    dissassembleChunk(&chunk, "Nick's Chunk");
    freeChunk(&chunk);
    
    return 0;
}
