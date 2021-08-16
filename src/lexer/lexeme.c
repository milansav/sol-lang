#include "lexeme.h"

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row)
{
    Lexeme l;
    
    l.type = type;
    l.label = label;
    l.column = col;
    l.row = row;

    return l;
}

LexemeArr* lexemearr_create(void)
{
    LexemeArr* la = malloc(sizeof(LexemeArr));

    la->count = 0;
    la->size = LA_DEFAULT_SIZE;
    la->arr = malloc(sizeof(Lexeme) * la->size);

    return la;
}

void lexemearr_add(LexemeArr* la, Lexeme l)
{
    if(la->count + 1 >= la->size)
    {
        la->size += LA_DEFAULT_INC;
        la->arr = realloc(la->arr, la->size);
    }

    la->arr[la->count] = l;
    la->count++;
}
