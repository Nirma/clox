//
//  VM.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/02/27.
//

#include "VM.h"
#include "Chunk.h"
#include "Value.h"
#include "Compiler.h"

VM virtualMachine;

void initVM(void) {
    resetStack();
}

void freeVM(void) {
    
}

void push(Value value) {
    *virtualMachine.stackTop = value;
    virtualMachine.stackTop++;
}

int pop() {
    virtualMachine.stackTop--;
    return *virtualMachine.stackTop;
}

void resetStack() {
    virtualMachine.stackTop = virtualMachine.stack;
}



INTERPRETRESULT run(void) {
#define READ_BYTE() (*virtualMachine.ip++)
    uint8_t instruction;
    for (;;) {
        
#ifdef DEBUG_7
        printf("\n=== START OF STACK === \n");
        for (Value *pos = virtualMachine.stack; pos < virtualMachine.stackTop; pos++) {
            printf("-- STACK [%ld] = %f\n", pos - virtualMachine.stack, *pos);
        }
        printf("=== END OF STACK === \n\n");
#endif
        
        switch (instruction = READ_BYTE()) {
            case OP_RETURN:
                printf("OP_RETURN: Returning %d\n", pop());
                return INTERPRET_OK;
            case OP_CONST:
            {
                int offset = (*virtualMachine.ip++);
                Value value = virtualMachine.chunk->values.values[offset];
                push(value);
                printf("OP_CONST: Pushed a value: %f\n", value);
                break;
            }
            case OP_NEGATE:
            {
                Value nextValue = -pop();
                push(nextValue);
                
#ifdef DEBUG
                printf("OP_NEGATE: %f\n", nextValue);
#endif
                break;
            }
            case OP_ADD:
            {
                Value b = pop();
                Value a = pop();
                Value result = a + b;
                push(result);
                
#ifdef DEBUG
                printf("OP_ADD: %f + %f = %f\n", a, b, result);
#endif
                break;
            }
            case OP_SUBTRACT:
            {
                Value b = pop();
                Value a = pop();
                Value result = a - b;
                push(result);
                
#ifdef DEBUG
                printf("OP_SUBTRACT: %f - %f = %f\n", a, b, result);
#endif
                break;
            }
            case OP_MULT:
            {
                Value b = pop();
                Value a = pop();
                Value result = a * b;
                push(result);
                
#ifdef DEBUG
                printf("OP_SUBTRACT: %f * %f = %f\n", a, b, result);
#endif
                break;
            }
            case OP_DIVIDE:
            {
                Value b = pop();
                Value a = pop();
                Value result = a / b;
                push(result);
                
#ifdef DEBUG
                printf("OP_SUBTRACT: %f / %f = %f\n", a, b, result);
#endif
                break;
            }
        }
    }
#undef READ_BYTE
    return INTERPRET_OK;
}

INTERPRETRESULT interpretChunk(Chunk *chunk) {
    virtualMachine.chunk = chunk;
    virtualMachine.ip = virtualMachine.chunk->code;
    return run();
}

INTERPRETRESULT interpret(const char *source) {
    compile(source);
    return INTERPRET_OK;
}
