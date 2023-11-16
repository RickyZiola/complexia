#include "../parser.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    Lexer lexer = { "3 + 5 * 4", 0, {0, false, NULL}};
    Bytecode out = malloc(1024);
    Parser parser = { &lexer, out };
    compile(&parser);

    disasm(out);
    return 0;
}