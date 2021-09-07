#include "parser.h"

LexemeArr* la;
Lexeme* lexemes;
Symbol sym;

static void next()
{
    lexemes += sizeof(Lexeme*);
    sym = lexemes->type;
}

Ast* parser_create_ast(LexemeArr* l)
{
    la = l;
    lexemes = la->arr;
}

static Node block()
{

}

static Node statement()
{

}

static Node expression()
{

}

static Node condition()
{

}

static Node term()
{

}

static Node factor()
{

}
