#include "../parser.h"

int main(int argc, char **argv) {
    Lexer lexer = { "3 + 5 * 4", 0, {0, false, NULL}};
    Parser parser = { &lexer, NULL };

    compile(&parser);

    return 0;
}