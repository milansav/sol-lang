#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "../common/common.h"

typedef struct Program Program;
typedef struct Statement Statement;
typedef struct StatementArr StatementArr;
typedef struct Expression Expression;
typedef struct Declaration Declaration;
typedef struct BinOp BinOp;

typedef enum StatementType {
    STTMNT_NONE, STTMNT_FUNCTION, STTMNT_IF, STTMNT_ELSE, STTMNT_ELSEIF, STTMNT_WHILE, STTMNT_DECLARATION
} StatementType;

typedef enum ExpressionType {
    EXPR_NONE, EXPR_NUM_LITERAL, EXPR_STR_LITERAL, EXPR_CHAR_LITERAL, EXPR_ASSIGN, EXPR_BINOP
} ExpressionType;

typedef enum DeclarationType {
    DECL_NONE, DECL_LET, DECL_CONST
} DeclarationType;

typedef enum BinOpType {
    BINOP_NONE, BINOP_SUM, BINOP_SUB, BINOP_DIV, BINOP_DIVT, BINOP_MUL, BINOP_POW
} BinOpType;

typedef struct Program {
    StatementArr* arr;
} Program;

typedef struct Statement {
    StatementType type;
    union {
        Declaration* declaration;
        Expression* expression;
    } value;
} Statement;

Statement* statement_construct();
void statement_deconstruct(Statement* statement);

typedef struct StatementArr {
    u8 size;
    u8 count;
    Statement* arr;
} StatementArr;

StatementArr* statementarr_construct();
void statementarr_deconstruct();

typedef struct Expression {
    ExpressionType type;
    union {
        int int_literal;
        char char_literal;
        char* str_literal;
        Expression* expr;
        BinOp* binop;
    } value;
} Expression;

Expression* expression_construct();
void expression_deconstruct(Expression* expression);

typedef struct ExpressionArr {
    u8 size;
    u8 count;
    Expression* arr;
} ExpressionArr;

ExpressionArr* expressionarr_construct();
void expressionarr_deconstruct();

typedef struct Declaration {
    DeclarationType type;
} Declaration;

Declaration* declaration_construct();
void declaration_deconstruct(Declaration* declaration);

typedef struct BinOp {
    BinOpType type;
    Expression* left;
    Expression* right;
} BinOp;

BinOp* binop_construct();
void binop_deconstruct(BinOp* binop);

#endif