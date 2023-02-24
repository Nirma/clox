//
//  Debug.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/24.
//

#ifndef Debug_h
#define Debug_h

#include <stdio.h>
#include "Chunk.h"

void dissassembleChunk(Chunk *chunk, const char* name);

int simpleInstruction(const char* name, int offset);

int disassembleInstruction(Chunk *chunk, int offset);

int constantInstruction(const char* name, Chunk *chunk, int offset);
#endif /* Debug_h */
