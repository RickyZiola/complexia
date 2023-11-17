#include "backend.h"
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
const char *opcode_to_str(Opcode opcode) {
    switch (opcode) {
        STRINGIFY_ENUM_CASE(OP_CONST)
        STRINGIFY_ENUM_CASE(OP_ADD)
        STRINGIFY_ENUM_CASE(OP_SUB)
        STRINGIFY_ENUM_CASE(OP_MUL)
        STRINGIFY_ENUM_CASE(OP_DIV)
        STRINGIFY_ENUM_CASE(OP_POW)
        STRINGIFY_ENUM_CASE(OP_DONE)
        default: return "UNKNOWN_OPCODE";
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

void print_tok(Token tok) {
    if (tok.typ == TOKEN_NUMBER_LITERAL) {
        printf("%s: %f + %fi\n", tok_typ_to_str(tok.typ), tok.data.num.real, tok.data.num.imag);
    } else {
        printf("%s: '%s'\n", tok_typ_to_str(tok.typ), tok.data.str);
    }
}
void print_comp(Complex c) {
    printf("(%f + %fi)\n", c.real, c.imag);
}

static bool next_is(Parser *p, TokenType typ) {
    return p->l->next.typ == typ;
}
static bool consume(Parser *p, TokenType typ) {
    if (!next_is(p, typ)) return false;
    (void) scan(p->l);
    return true;
}

void emitOp(Parser *p, Opcode op) {
    p->out.data[p->out_idx++] = op;
}
void emitComp(Parser *p, Complex c) {
    *((float *)(p->out.data+(p->out_idx))) = c.real;
    p->out_idx += sizeof(float);
    *((float *)(p->out.data+(p->out_idx))) = c.imag;
    p->out_idx += sizeof(float);
}

void compile(Parser *p) {
    expr(p);
    emitOp(p, OP_DONE);
}
void expr(Parser *p) {
    term(p);

}
void term(Parser *p) {
    // left operand
    factor(p);

    while (next_is(p, TOKEN_PLUS) || next_is(p, TOKEN_MINUS)) {
        bool plus, minus;
        plus  = consume(p,  TOKEN_PLUS);
        minus = consume(p, TOKEN_MINUS);

        if (plus && minus) {
            printf("Expected expression after plus/minus token.\n");
            exit(EXIT_FAILURE);
        }

        // right operand
        factor(p);
        if (plus ) emitOp(p, TOKEN_PLUS );
        if (minus) emitOp(p, TOKEN_MINUS);
    }
}
void factor(Parser *p) {
    // left operand
    exponent(p);

    while (next_is(p, TOKEN_MULT) || next_is(p, TOKEN_DIV)) {
        bool mult, div;
        mult = consume(p, TOKEN_MULT);
        div  = consume(p, TOKEN_DIV );

        if (mult && div) {
            printf("Expected expression after plus/minus token.\n");
            exit(EXIT_FAILURE);
        }

        // right operand
        exponent(p);
        if (mult) emitOp(p, TOKEN_MULT);
        if (div ) emitOp(p, TOKEN_DIV );
    }
}
void exponent(Parser *p) {
    // left operand
    primary(p);

    while (next_is(p, TOKEN_POW)) {
        consume(p, TOKEN_POW);

        // right operand
        primary(p);
        emitOp(p, OP_POW);
    }
}
void primary(Parser *p) {
    if (next_is(p, TOKEN_NUMBER_LITERAL)) {
        emitOp(p, OP_CONST);
        Token n = scan(p->l);
        emitComp(p, n.data.num);
        return;
    }
    if (next_is(p, TOKEN_LEFT_PAREN)) return paren(p);
    printf("Expected number or parentheses. %s\n", tok_typ_to_str(p->l->next.typ));
    exit(EXIT_FAILURE);
}
void paren(Parser *p) {
    if (consume(p, TOKEN_LEFT_PAREN)) {
        expr(p);
        if (!consume(p, TOKEN_RIGHT_PAREN)) {
            printf("Expected closing parenthese.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        expr(p);
    }
}

void disasm(Bytecode bc) {
    unsigned int idx = 0;
    while (idx < bc.length) {
        switch (bc.data[idx]) {
            case OP_CONST:
                printf("OP_CONST (%f + %fi)\n", *((float *)(bc.data + idx + 1)), *((float *)(bc.data + idx + 1 + sizeof(float))));
                idx += 1 + sizeof(float) * 2;
                break;
            
            case OP_ADD:
            case OP_SUB:
            case OP_MUL:
            case OP_DIV:
            case OP_POW:
                printf("%s\n", opcode_to_str(bc.data[idx]));
                ++idx;
                break;

            case OP_DONE:
                printf("OP_DONE\n");
                idx = bc.length;
                break;
            
            default: printf("UNKNOWN\n");
        }
    }
}

Complex complex_add(Complex z1, Complex z2) {
    return (Complex) { z1.real + z2.real, z1.imag + z2.imag };
}
Complex complex_sub(Complex z1, Complex z2) {
    return (Complex) { z1.real - z2.real, z1.imag - z2.imag };
}
Complex complex_mul(Complex z1, Complex z2) {
    Complex result;
    result.real = z1.real * z2.real - z1.imag * z2.imag;
    result.imag = z1.real * z2.imag + z1.imag * z2.real;
    return result;
}
Complex complex_div(Complex z1, Complex z2) {
    Complex result;
    float denominator = z2.real * z2.real + z2.imag * z2.imag;

    result.real = (z1.real * z2.real + z1.imag * z2.imag) / denominator;
    result.imag = (z1.imag * z2.real - z1.real * z2.imag) / denominator;

    return result;
}
Complex complex_pow(Complex z1, Complex z2) {
    // Convert z1 to polar form
    float r1 = sqrtf(z1.real * z1.real + z1.imag * z1.imag);
    float theta1 = atan2f(z1.imag, z1.real);

    // Compute the power in polar form
    float result_r = powf(r1, z2.real) * expf(-z2.imag * theta1);
    float result_theta = z2.real * theta1 + z2.imag * logf(r1);

    // Convert the result back to Cartesian form
    Complex result;
    result.real = result_r * cosf(result_theta);
    result.imag = result_r * sinf(result_theta);

    return result;
}

Complex run(Bytecode bc) {
    Complex stack[256]; // TODO: dynamically grow this if needed
    unsigned int sp = 0;
    unsigned int idx = 0;
    Complex l,r;
    while (idx < bc.length) {
        switch (bc.data[idx]) {
            case OP_CONST:
                Complex z = { *((float *)(bc.data + idx + 1)), *((float *)(bc.data + idx + 1 + sizeof(float))) };
                stack[sp++] = z;
                idx += 1 + sizeof(float) * 2;
                break;
            
            case OP_ADD:
                r = stack[--sp];
                l = stack[--sp];
                stack[sp++] = complex_add(l,r);
                ++idx;
                break;
            case OP_SUB:
                r = stack[--sp];
                l = stack[--sp];
                stack[sp++] = complex_sub(l,r);
                ++idx;
                break;
            case OP_MUL:
                r = stack[--sp];
                l = stack[--sp];
                stack[sp++] = complex_mul(l,r);
                ++idx;
                break;
            case OP_DIV:
                r = stack[--sp];
                l = stack[--sp];
                stack[sp++] = complex_div(l,r);
                ++idx;
                break;
            case OP_POW:
                r = stack[--sp];
                l = stack[--sp];
                stack[sp++] = complex_pow(l,r);
                ++idx;
                break;

            case OP_DONE:
                return stack[--sp];
                break;
            
            default: printf("UNKNOWN\n");
        }
    }
}