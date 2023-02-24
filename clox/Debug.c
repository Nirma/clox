//
//  Debug.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/24.
//

#include "Debug.h"
#import "Chunk.h"

void dissassembleChunk(Chunk *chunk, const char* name) {
    printf("==== %s ====\n", name);
    for (int offset=0; offset<chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int constantInstruction(const char* name, Chunk *chunk, int offset) {
    uint8_t location = chunk->code[offset + 1];
    uint8_t value = chunk->values.values[location];
    printf("OP_CONST ");
    printf(" NAME: %s", name);
    printf(" Value: %d\n\n", value);
    
    return offset + 2;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    printf("%04d", offset);
    uint8_t instruction = chunk->code[offset];
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset-1]) {
        printf(" | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }
    
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONST:
            return constantInstruction("Constant Instruction --", chunk, offset);
        default:
            printf("Unknown Instruction");
            return offset + 1;
    }
}
