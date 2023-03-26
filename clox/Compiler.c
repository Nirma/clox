//
//  Compiler.c
//  clox
//
//  Created by Nicholas Maccharoli on 2023/03/10.
//

#include "Compiler.h"
#include "Scanner.h"
#include "VM.h"
#include "Chunk.h"

typedef void (*ParserFN)(void);

typedef enum {
  PREC_NONE,
  PREC_ASSIGNMENT,  // =
  PREC_OR,          // or
  PREC_AND,         // and
  PREC_EQUALITY,    // == !=
  PREC_COMPARISON,  // < > <= >=
  PREC_TERM,        // + -
  PREC_FACTOR,      // * /
  PREC_UNARY,       // ! -
  PREC_CALL,        // . ()
  PREC_PRIMARY
} Precedence;

typedef struct {
    ParserFN infix;
    ParserFN prefix;
    Precedence prec;
} ParserRule;

typedef struct {
    Token previous;
    Token current;
    bool hadError;
    bool panicMode;
} Parser;

Parser parser;




Chunk *compilingChunk;

static Chunk* currentChunk(void) {
    return compilingChunk;
}

void emitBytes(uint8_t, uint8_t);

static void errorAt(Token* token, const char* message) {
    if (parser.panicMode) return;
    parser.panicMode = true;
    
    fprintf(stderr, "[line %d] Error", token->line);
    
    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // nothing
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }
    
    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

static void errorAtCurrent(const char *message) {
    errorAt(&parser.current, message);
}

static void error(const char* message) {
    errorAt(&parser.previous, message);
}

static int makeConstant(double value) {
    int pos = addValue(currentChunk(), value);
    if (pos > UINT8_MAX) {
        error("Too many constants in one chunk.");
        return 0;
    }
    
    return (uint8_t) pos;
}

static void emitConstant(double value) {
    emitBytes(OP_CONST, makeConstant(value));
}

static void number() {
    double value = strtod(parser.previous.start, NULL);
    emitConstant(value);
}

static void expression() {
    
}


void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void endCompiler(void) {
    emitByte(TOKEN_RETURN);
}

static void advanceToken() {
    parser.previous = parser.current;
    
    for (;;) {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR) break;
    }
    
    // had error code
    
    errorAtCurrent(parser.current.start);
    
}


static void consume(TokenType type, const char *message) {
    if (parser.current.type == type) {
        advanceToken();
        return;
    }
    
    errorAtCurrent(message);
}



bool compile(Chunk *chunk, const char *source) {
    initScanner(source);
    compilingChunk = chunk;
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
    return true;
}
