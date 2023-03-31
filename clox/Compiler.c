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


typedef void (*ParserFN)(void);

void emitConstant(double);

static void number() {
    double value = strtod(parser.previous.start, NULL);
    emitConstant(value);
}

typedef struct {
    ParserFN prefix;
    ParserFN infix;
    Precedence prec;
} ParserRule;




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

 void emitConstant(double value) {
    emitBytes(OP_CONST, makeConstant(value));
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
        
        // had error code
        
        errorAtCurrent(parser.current.start);
    }
}

// ====

ParserRule getRuleFor(TokenType type);
void parsePrecedence(Precedence);

static void unary(void) {
    // advanceToken();
    TokenType operator = parser.previous.type;
    parsePrecedence(PREC_UNARY);
    
    switch (operator) {
        case TOKEN_MINUS:
            emitByte(OP_NEGATE);
    }
}

static void binary(void) {
    TokenType operator = parser.current.type;
    ParserRule rule = getRuleFor(parser.current.type);
    advanceToken();
    
    parsePrecedence(rule.prec + 1);
    
    switch (operator) {
        case TOKEN_PLUS:
            emitByte(OP_ADD);
            break;
        case TOKEN_MINUS:
            emitByte(OP_SUBTRACT);
            break;
        case TOKEN_STAR:
            emitByte(OP_MULT);
            break;
        case TOKEN_SLASH:
            emitByte(OP_DIVIDE);
            break;
        default:
            error("Undefined binary op");
            
    }
}

void expression(void);
void consume(TokenType type, const char *message);

static void grouping() {
    consume(TOKEN_LEFT_PAREN, "Expected left paren");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expected closing parenthesis!");
}

ParserRule parserRules[] = {
  [TOKEN_LEFT_PAREN]    = {grouping, NULL,   PREC_NONE},
  [TOKEN_RIGHT_PAREN]   = {NULL,     NULL,   PREC_NONE},
  [TOKEN_LEFT_BRACE]    = {NULL,     NULL,   PREC_NONE},
  [TOKEN_RIGHT_BRACE]   = {NULL,     NULL,   PREC_NONE},
  [TOKEN_COMMA]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_DOT]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_MINUS]         = {unary,    binary, PREC_TERM},
  [TOKEN_PLUS]          = {NULL,     binary, PREC_TERM},
  [TOKEN_SEMICOLON]     = {NULL,     NULL,   PREC_NONE},
  [TOKEN_SLASH]         = {NULL,     binary, PREC_FACTOR},
  [TOKEN_STAR]          = {NULL,     binary, PREC_FACTOR},
  [TOKEN_BANG]          = {NULL,     NULL,   PREC_NONE},
  [TOKEN_BANG_EQUAL]    = {NULL,     NULL,   PREC_NONE},
  [TOKEN_EQUAL]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_EQUAL_EQUAL]   = {NULL,     NULL,   PREC_NONE},
  [TOKEN_GREATER]       = {NULL,     NULL,   PREC_NONE},
  [TOKEN_GREATER_EQUAL] = {NULL,     NULL,   PREC_NONE},
  [TOKEN_LESS]          = {NULL,     NULL,   PREC_NONE},
  [TOKEN_LESS_EQUAL]    = {NULL,     NULL,   PREC_NONE},
  [TOKEN_IDENTIFIER]    = {NULL,     NULL,   PREC_NONE},
  [TOKEN_STRING]        = {NULL,     NULL,   PREC_NONE},
  [TOKEN_NUMBER]        = {number,   NULL,   PREC_NONE},
  [TOKEN_AND]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_CLASS]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_ELSE]          = {NULL,     NULL,   PREC_NONE},
  [TOKEN_FALSE]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_FOR]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_FUN]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_IF]            = {NULL,     NULL,   PREC_NONE},
  [TOKEN_NIL]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_OR]            = {NULL,     NULL,   PREC_NONE},
  [TOKEN_PRINT]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_RETURN]        = {NULL,     NULL,   PREC_NONE},
  [TOKEN_SUPER]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_THIS]          = {NULL,     NULL,   PREC_NONE},
  [TOKEN_TRUE]          = {NULL,     NULL,   PREC_NONE},
  [TOKEN_VAR]           = {NULL,     NULL,   PREC_NONE},
  [TOKEN_WHILE]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_ERROR]         = {NULL,     NULL,   PREC_NONE},
  [TOKEN_EOF]           = {NULL,     NULL,   PREC_NONE},
};

ParserRule getRuleFor(TokenType type) {
    return parserRules[type];
}


void parsePrecedence(Precedence precedence) {
    advanceToken();
    ParserRule rule = getRuleFor(parser.previous.type);
    
    if ( rule.prefix == NULL ) {
        error("No rule defined as prefix");
    } else {
        rule.prefix();
    }
    
    rule = getRuleFor(parser.current.type);
    while( !isAtEnd() && precedence < rule.prec) {
        rule.infix();
    }
}

void expression() {
    parsePrecedence(PREC_ASSIGNMENT);
}
// ====

void consume(TokenType type, const char *message) {
    if (parser.current.type == type) {
        advanceToken();
        return;
    }
    
    errorAtCurrent(message);
}

bool compile(Chunk *chunk, const char *source) {
    initScanner(source);
    compilingChunk = chunk;
    
    advanceToken();
    expression();
    consume(TOKEN_EOF, "Expected EOF");
    endCompiler();
    
    return !parser.hadError;
}
