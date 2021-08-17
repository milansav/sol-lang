#include "./lexer/lexer.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    LexemeArr* la = lexer_start("Hello        World       #HELLO WORLD\n     123\0");
    
    for(int i = 0; i < la->count; i++)
    {
        printf("%s\n", la->arr[i].label);
    }
    
    return 0;
}
