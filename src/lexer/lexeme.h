#ifndef LEXEME_H
#define LEXEME_H

#include <stdlib.h>
#include <stdio.h>
#include "../common/common.h"

#define LA_DEFAULT_SIZE 32 //Default LexemeArr size
#define LA_DEFAULT_INC  16 //Default LexemeArr size increase constant

typedef enum {
    //Binary ops
    SUM, SUB, MUL, DIV, MOD, ASSIGN, POW,
    //Bitwise ops
    AND, OR,
    //Parentheses
    LPAREN, RPAREN, LBRACKET, RBRACKET, LCRLBRACKET, RCRLBRACKET,
    //Deco
    PERIOD, SEMICOLON, COLON, QUERY, 
    //Keywords
    IF, ELSEIF, ELSE, FN, STRUCT, IMPORT,
    //Literals
    NUM, STR, CHAR, IDENT,
    //Math
    EQL, NQL, GQL, LQL,
    //Other
    INVALID, END
} Type;

/*Stores data about lexeme*/
typedef struct {
    Type        type;       //Enum type of lexeme
    char*       label;      //String label of lexeme
    u8          column;     //Column at which lexeme starts
    u8          row;        //Row at which lexeme starts
} Lexeme;

typedef struct {
    unsigned int size;
    unsigned int count;
    Lexeme* arr;
} LexemeArr;

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row);
void lexeme_remove(Lexeme* l);

LexemeArr* lexemearr_create();
void lexemearr_add(LexemeArr* la, Lexeme l);
void lexemearr_remove(LexemeArr* la);

#endif
