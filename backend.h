#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum Opcode {
    OP_CONST,
    OP_ADD, OP_SUB,
    OP_MUL, OP_DIV, OP_NEG,
    OP_SIN, OP_COS,
    OP_POW, OP_DONE
} Opcode;

typedef enum TokenType {
    TOKEN_NUMBER_LITERAL,
    TOKEN_PLUS, TOKEN_MINUS,
    TOKEN_MULT, TOKEN_DIV,
    TOKEN_POW, TOKEN_HASH,
    TOKEN_ID, TOKEN_EQ,
    TOKEN_SIN, TOKEN_COS,
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,

    TOKEN_EOF, TOKEN_UNKNOWN
} TokenType;

#define STRINGIFY_ENUM_CASE(enumValue) case enumValue: return #enumValue;
const char *tok_typ_to_str(TokenType tokenType);
const char *opcode_to_str(Opcode opcode);

typedef struct Complex {
    float real;
    float imag;
} Complex;

typedef struct Token {
    TokenType typ;
    bool exists;
    union {
        char *str;
        Complex num;
    } data;
} Token;

typedef struct Lexer {
    char *input;
    unsigned int idx;

    Token next;
} Lexer;

typedef struct Bytecode {
    unsigned int length;
    unsigned char *data;
} Bytecode;

typedef struct Parser {
    Lexer *l;
    Bytecode out;
    unsigned int out_idx;
} Parser;

char next(Lexer *lexer);
char current(Lexer *lexer);
bool at_end(Lexer *lexer);
Token scan(Lexer *lexer);
void print_tok(Token tok);
void print_comp(Complex c);

void compile(Parser *parser);  // Compile. This is essentially an alias for expr
void expr(Parser *parser);     // Expression
void paren(Parser *parser);    // Parenthesized expression
void exponent(Parser *parser); // Exponent (a^b)
void factor(Parser *parser);   // Mult/div
void unary(Parser *parser);    // Negation, functions (sin, cos, log, etc.)
void term(Parser *parser);     // Add/sub
void primary(Parser *parser);  // Number constant

void disasm(Bytecode bc);

Complex complex_add(Complex z1, Complex z2);
Complex complex_sub(Complex z1, Complex z2);
Complex complex_mul(Complex z1, Complex z2);
Complex complex_div(Complex z1, Complex z2);
Complex complex_pow(Complex z1, Complex z2);

Complex run(Bytecode bc);

#endif