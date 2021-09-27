#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexeme.h"
#include "../common/common.h"
#include "../common/keywords.h"
#include "../common/debug.h"

typedef int Symbol;

typedef enum {
    node
} NodeType;

typedef struct node {

} Node;

typedef struct ast {
    u8 size;
    u8 count;
    Node* arr;
} Ast;

Ast* ast_construct(void);
void ast_deconstruct(Ast* ast);

void ast_append_node(Ast* ast, Node node);

Ast* parser_start(LexemeArr* l);

#endif
