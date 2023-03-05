//
//  VM.h
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/27.
//

#ifndef VM_h
#define VM_h

#include "Chunk.h"
#include "Value.h"

#define STACK_MAX 256

typedef struct {
    Chunk *chunk;
    uint8_t *ip;
    Value stack[STACK_MAX];
    Value *stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} INTERPRETRESULT;



void initVM(void);

void freeVM(void);

INTERPRETRESULT interpretChunk(Chunk *chunk);

void push(Value value);

int pop(void);

void resetStack(void);

INTERPRETRESULT run(void);

#endif /* VM_h */
