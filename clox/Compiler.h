//
//  Compiler.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/03/10.
//

#ifndef Compiler_h
#define Compiler_h

#include "Scanner.h"
#include "Chunk.h"
#include <stdio.h>

bool compile(Chunk *chunk, const char* source);



#endif /* Compiler_h */

