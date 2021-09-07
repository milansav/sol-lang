#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexeme.h"
#include "../common/common.h"

typedef int Symbol;

typedef struct node {

} Node;

typedef struct ast {
    u8 size;
    u8 count;
    Node* arr;
} Ast;

Ast* parser_create_ast(LexemeArr* l);

static Node block();
static Node statement();
static Node expression();
static Node condition();
static Node term();
static Node factor();

static void next();
static Symbol curr_s();
static int check(Symbol s);
static int expect(Symbol s);
#endif
