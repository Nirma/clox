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

void repl(void) {
    char line[1024];
    
    for (;;) {
        printf("> ");
        
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        
        interpret(line);
    }
}

void runFile(const char *filename) {
    
}

int main(int argc, const char * argv[]) {
    initVM();
    
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage clox [path]/n");
        exit(64);
    }
  

    return 0;
}
