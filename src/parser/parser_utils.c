#include "./parser_utils.h"

Statement* statement_construct()
{
    Statement* statement = malloc(sizeof(Statement));
    statement->type = STTMNT_NONE;
    return statement;
}

void statement_deconstruct(Statement* statement)
{
    if(!statement) return;
    switch (statement->type)
    {
    case STTMNT_DECLARATION:
    if(statement->value.declaration) declaration_deconstruct(statement->value.declaration);
    break;
    }
    free(statement);
}

Expression* expression_construct()
{
    Expression* expression = malloc(sizeof(Expression));
    expression->type = EXPR_NONE;
    return expression;
}

void expression_deconstruct(Expression* expression)
{
    if(!expression) return;
    //TODO: Free elements, when Expression struct is complete
    switch(expression->type)
    {
        case EXPR_NUM_LITERAL:
        break;
        case EXPR_STR_LITERAL:
        if(expression->value.str_literal) free(expression->value.str_literal);
        break;
        case EXPR_CHAR_LITERAL:
        break;
        case EXPR_ASSIGN:
        if(expression->value.expr) expression_deconstruct(expression->value.expr);
        break;
        case EXPR_BINOP:
        if(expression->value.binop) binop_deconstruct(expression->value.binop);
        break;
    }
    free(expression);
}

Declaration* declaration_construct()
{
    Declaration* declaration = malloc(sizeof(Declaration));
    declaration->type = DECL_NONE;
    return declaration;
}

void declaration_deconstruct(Declaration* declaration)
{
    if(!declaration) return;
    //TODO: Free elements, when Declaration struct is complete
    free(declaration);
}

BinOp* binop_construct()
{
    BinOp* binop = malloc(sizeof(BinOp));
    binop->type = BINOP_NONE;

    return binop;
}

void binop_deconstruct(BinOp* binop)
{
    if(!binop) return;
    if(binop->left) free(binop->left);
    if(binop->right) free(binop->right);
    free(binop);
}