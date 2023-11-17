#include "../backend.h"

int main(int argc, char **argv) {
    Lexer lexer = { "-35", 0, {0, false, NULL}};

    Token tok;

    while ((tok = scan(&lexer)).typ != TOKEN_EOF) {
        print_tok(tok);
    }

    return 0;
}