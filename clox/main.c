//
//  main.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/22.
//

#include <stdio.h>
#include "Chunk.h"

int main(int argc, const char * argv[]) {
    Chunk chunk;
    
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    freeChunk(&chunk);
    
    return 0;
}
