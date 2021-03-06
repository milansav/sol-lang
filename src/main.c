#include "./lexer/lexer.h"
#include "./lexer/lexeme.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    LexemeArr* la = lexer_start("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\0");
    
    for(int i = 0; la->arr[i].type != END; i++)
    {
        printf("%s\n", la->arr[i].label);
    }

    lexemearr_remove(la);

    return 0;
}
