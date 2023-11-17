#include "../backend.h"
#include <stdlib.h>

int main(int argc, char **argv) {
    Lexer lexer = { "3 + 5 * 4^e", 0, {0, false, NULL}};
    Bytecode out = { 1024, malloc(1024) };
    Parser parser = { &lexer, out, 0 };
    compile(&parser);

    print_comp(run(out));
    return 0;
}