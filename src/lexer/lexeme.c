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

LexemeArr* lexemearr_create()
{
    LexemeArr* la = malloc(sizeof(LexemeArr));

    la->arr = malloc(sizeof(Lexeme) * 16);

    la->count = 0;
    la->size = 16;

    return la;
}

void lexemearr_add(LexemeArr* la, Lexeme l)
{
    if(la->count >= la->size)
    {
        la->size *= 2;
        la->arr = realloc(la->arr, la->size * sizeof(Lexeme));
    }

    la->arr[la->count] = l;
    la->count++;
}

void lexemearr_remove(LexemeArr* la)
{
    for(u8 i = 0; la->arr[i].type != END; i++)
    {
        free(la->arr[i].label);
    }

    free(la->arr);
    free(la);
}
