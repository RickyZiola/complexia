#include "../parser.h"

int main(int argc, char **argv) {
    Lexer lexer = { "i_am_an _identifier 23i i 5 3i pi e 23+5i ( +- */^ ) 85 * (e^(i*pi))", 0, {0, false, NULL}};

    Token tok;

    while ((tok = scan(&lexer)).typ != TOKEN_EOF) {
        print(tok);
    }

    return 0;
}