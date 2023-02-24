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
    
    printf("\n\n==== %s ====\n", name);
    printf("Offset: %4d\n", offset);
    printf("Value: %d\n\n", value);
    
    return offset + 2;
}

int disassembleInstruction(Chunk *chunk, int offset) {
    uint8_t instruction = chunk->code[offset];
    printf("Offset: %04d ", offset);
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
