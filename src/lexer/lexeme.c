#include "lexeme.h"

char TypeString[TYPE_COUNT][TYPE_LENGTH] = 
{"SUM\0", "SUB\0", "MUL\0", "DIV\0", "DIVT\0", "MOD\0", "ASSIGN\0", "POW\0", "INC\0", "DEC\0",
 "AND\0", "OR\0", "NOT\0", "XOR\0", "LPAREN\0", "RPAREN\0", "LBRACKET\0", "RBRACKET\0", "LCRLBRACKET\0",
 "RCRLBRACKET\0", "PERIOD\0", "SEMICOLON\0", "COLON\0", "QUERY\0", "COMMA\0" ,"IF\0", "ELSEIF\0", "ELSE\0", "FN\0",
 "STRUCT\0", "IMPORT\0", "REF\0", "LET\0", "CONST\0", "TYPE\0", "NUM\0", "STR\0", "CHAR\0", "IDENT\0", "EQL\0", "NQL\0", "GQL\0",
 "LQL\0", "LSS\0", "GTR\0", "INVALID\0", "END\0"};

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row)
{
    Lexeme l;
    
    l.type = type;
    l.label = label;
    l.column = col;
    l.row = row;

    return l;
}

LexemeArr* lexemearr_construct()
{
    LexemeArr* la = malloc(sizeof(LexemeArr));

    la->arr = malloc(sizeof(Lexeme) * 16);

    la->count = 0;
    la->size = 16;

    return la;
}

void lexeme_deconstruct(Lexeme lexeme)
{
    if(!lexeme.label)
    {
        if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_LEXER))
        {
            g_logln("lexeme.c : lexeme_deconstruct: Nothing to deconstruct");
        }
        return;
    }
    free(lexeme.label);
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

void lexemearr_deconstruct(LexemeArr* la)
{
    if(!la)
    {
        if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_LEXER))
        {
            g_logln("lexeme.c : lexemearr_deconstruct: Nothing to deconstruct");
        }
        return;
    }
    if(!la->arr)
    {
        if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_LEXER))
        {
            g_logln("lexeme.c : lexemearr_deconstruct: Nothing to deconstruct");
        }
        return;
    }

    for(u8 i = 0; la->arr[i].type != END; i++)
    {
        lexeme_deconstruct(la->arr[i]);
    }

    free(la->arr);
    free(la);
}
