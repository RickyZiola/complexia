#include "parser.h"
#include <ctype.h>
#include <math.h>

static bool is_identifier(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

const char* tok_typ_to_str(TokenType tokenType) {
    switch (tokenType) {
        STRINGIFY_ENUM_CASE(TOKEN_NUMBER_LITERAL)
        STRINGIFY_ENUM_CASE(TOKEN_PLUS)
        STRINGIFY_ENUM_CASE(TOKEN_MINUS)
        STRINGIFY_ENUM_CASE(TOKEN_MULT)
        STRINGIFY_ENUM_CASE(TOKEN_DIV)
        STRINGIFY_ENUM_CASE(TOKEN_POW)
        STRINGIFY_ENUM_CASE(TOKEN_ID)
        STRINGIFY_ENUM_CASE(TOKEN_EQ)
        STRINGIFY_ENUM_CASE(TOKEN_LEFT_PAREN)
        STRINGIFY_ENUM_CASE(TOKEN_RIGHT_PAREN)
        STRINGIFY_ENUM_CASE(TOKEN_EOF)
        STRINGIFY_ENUM_CASE(TOKEN_UNKNOWN)
        default: return "UNKNOWN_TOKEN_TYPE";
    }
}

char next(Lexer *l) {
    return l->input[l->idx++];
}
char current(Lexer *l) {
    return l->input[l->idx];
}
bool at_end(Lexer *l) {
    return l->idx >= strlen(l->input);
}

static Token scan_single(Lexer *l) {
    while (isspace(next(l)));
    --l->idx;
    if (at_end(l)) return (Token){ TOKEN_EOF, true, NULL };
    if (is_identifier(current(l))) {
        unsigned int length = 0;
        while (is_identifier(next(l))) ++length; // Find the length of the identifier
        char *id = malloc(length + 1);
        memcpy(id, l->input + l->idx - length - 1, length * sizeof(char));
        --l->idx;
        id[length] = 0; // null-terminated string

            // Imaginary number 'i' = sqrt(-1)
            // Proof: Girolamo Cardano made it up
        if (length == 1 && id[0] == 'i') return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { 0.0f, 1.0f } }};

            // Euler's irrational constant 'e' ~= 2.7182
            // (d/dx)e^x = e^x
        if (length == 1 && id[0] == 'e') return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { 2.7182818284590452353602874713527, 0.0f } }};

            // Pi = ~= 3.1415
            // Ratio of circle's radius to circumference
        if (length == 2 && !strcmp(id, "pi")) return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { 3.14159265358979323846264338327950288419716939937510 , 0.0f } }};

        return (Token){ TOKEN_ID, true, id };
    }

    if (current(l) == '.' || isdigit(current(l))) {
        char *endPtr;
        float n = strtof(l->input + l->idx, &endPtr);
        l->idx = endPtr - l->input;

        if (current(l) == 'i') {
            (void) next(l);
            if (!is_identifier(current(l)))
                return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { 0.0f, n } }};
            else {
                return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { n, 0.0f } }};
                --l->idx;
            }
        } else {
            return (Token){ TOKEN_NUMBER_LITERAL, true, { .num = { n, 0.0f } }};
        }
    }

    if (current(l) == '+') { (void) next(l); return (Token){ TOKEN_PLUS,  "+" }; }
    if (current(l) == '-') { (void) next(l); return (Token){ TOKEN_MINUS, "-" }; }
    if (current(l) == '*') { (void) next(l); return (Token){ TOKEN_MULT,  "*" }; }
    if (current(l) == '/') { (void) next(l); return (Token){ TOKEN_DIV,   "/" }; }
    if (current(l) == '^') { (void) next(l); return (Token){ TOKEN_POW,   "^" }; }

    if (current(l) == '=') { (void) next(l); return (Token){ TOKEN_EQ,    "=" }; }
    if (current(l) == '(') { (void) next(l); return (Token){ TOKEN_LEFT_PAREN,  "(" }; }
    if (current(l) == ')') { (void) next(l); return (Token){ TOKEN_RIGHT_PAREN, ")" }; }

    printf("Unexpected character '%c'.\n", current(l));
    return (Token){ TOKEN_UNKNOWN, true, NULL };
}

Token scan(Lexer *l) {
    if (!l->next.exists) {
        Token c = scan_single(l);
        l->next = scan_single(l);
        return c;
    } else {
        Token c = l->next;
        l->next = scan_single(l);
        return c;
    }
}

void print(Token tok) {
    if (tok.typ == TOKEN_NUMBER_LITERAL) {
        printf("%s: %f + %fi\n", tok_typ_to_str(tok.typ), tok.data.num.real, tok.data.num.imag);
    } else {
        printf("%s: '%s'\n", tok_typ_to_str(tok.typ), tok.data.str);
    }
}

static bool next_is(Parser *p, TokenType typ) {
    return p->l->next.typ == typ;
}
static bool consume(Parser *p, TokenType typ) {
    if (!next_is(p, typ)) return false;
    (void) next(p->l);
    return true;
}

void compile(Parser *p) {
    expr(p);
}
void expr(Parser *p) {
    term(p);
}
void term(Parser *p) {
    // left operand
    factor(p);

    while (next_is(p, TOKEN_PLUS) || next_is(p, TOKEN_MINUS)) {
        if (consume(p, TOKEN_PLUS) && consume(p, TOKEN_MINUS)) {
            printf("Expected expression after plus or minus token.\n");
            exit(EXIT_FAILURE);
        }

        // right operand
        factor(p);
    }
}
void factor(Parser *p) {
    // left operand
    exponent(p);

    while (next_is(p, TOKEN_MULT) || next_is(p, TOKEN_DIV)) {
        if (consume(p, TOKEN_MULT) && consume(p, TOKEN_DIV)) {
            printf("Expected expression after mult or div token.\n");
            exit(EXIT_FAILURE);
        }

        // right operand
        exponent(p);
    }
}
void exponent(Parser *p) {
    // left operand
    paren(p);

    while (next_is(p, TOKEN_POW)) {
        consume(p, TOKEN_POW);

        // right operand
        paren(p);
    }
}
void paren(Parser *p) {
    if (consume(p, TOKEN_LEFT_PAREN)) {
        primary(p);
        if (!consume(p, TOKEN_RIGHT_PAREN)) {
            printf("Expected closing parenthese.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        primary(p);
    }
}
void primary(Parser *p) {
    if (!next_is(p, TOKEN_NUMBER_LITERAL)) {
        printf("Exptected number literal.\n");
        exit(EXIT_FAILURE);
    }
}