#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexeme.h"
#include "../common/common.h"
#include "../common/keywords.h"
#include "../common/debug.h"
#include "./parser_utils.h"

typedef int Symbol;

typedef struct ast {
    Program* program;
} Ast;

Ast* ast_construct(void);
void ast_deconstruct(Ast* ast);

Ast* parser_start(LexemeArr* l);

#endif
