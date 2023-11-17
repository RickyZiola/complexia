#include "../backend.h"
#include <stdio.h>

int main(int argc, char **argv) {
    while (1) {
        printf("> ");
        char buf[1024];
        buf[0] = '#';
        scanf("%s", buf+1);
        if (buf[1] == 'q') break;

        Lexer lexer = { buf, 0, {0, false, NULL}};
        Bytecode out = { 1024, malloc(1024) };
        Parser parser = { &lexer, out, 0 };
        compile(&parser);

        print_comp(run(out));
    }

    return 0;
}