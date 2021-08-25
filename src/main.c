#include "./lexer/lexer.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    LexemeArr* la = lexer_start("))}])}])}])}])}}])}])}])}])}]\0");
    return 0;
}
