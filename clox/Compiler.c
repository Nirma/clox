//
//  Compiler.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/03/10.
//

#include "Compiler.h"
#include "Scanner.h"
#include "VM.h"

void compile(const char *source) {
    initScanner(source);
    int line = -1;
    
    for (;;) {
        Token token = scanToken();
        if (token.line != line) {
            line = token.line;
            printf("%4d ", token.line);
        } else {
            printf(" | ");
        }
        printf("%2d '%.*s'\n", token.type, token.length, token.start);
        
        if (token.type == TOKEN_EOF) break;
    }
}
