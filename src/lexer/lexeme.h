#ifndef LEXEME_H
#define LEXEME_H

#include <stdlib.h>
#include <stdio.h>
#include "../common/common.h"
#include "../common/debug.h"

//TODO: rename lexemearr_create to lexemearr_construct & lexemearr_remove to lexemearr_deconstruct

#define LA_DEFAULT_SIZE 32 //Default LexemeArr size
#define LA_DEFAULT_INC  16 //Default LexemeArr size increase constant

typedef enum LexemeType{
    //Binary ops
//  +    -   *     /    //    %    =       ** or ^
//DIVT - How many times can an integer be divided (10 // 3 = 3)
    SUM, SUB, MUL, DIV, DIVT, MOD, ASSIGN, POW,
//  ++   --
    INC, DEC,
    //Bitwise ops
//  &    |   !    ~
    AND, OR, NOT, XOR,
    //Parentheses
    LPAREN, RPAREN, LBRACKET, RBRACKET, LCRLBRACKET, RCRLBRACKET,
    //Deco
//  .       ;          :      ?      ,
    PERIOD, SEMICOLON, COLON, QUERY, COMMA,
    //Keywords
    //All keyword types must be here & must be in same order as in keywords.c
    IF, ELSEIF, ELSE, FN, STRUCT, IMPORT, REF, LET, CONST, TYPE,
    //Literals
    //Don't change NUM's position in this enum
    NUM, STR, CHAR, IDENT,
    //Math
//  ==   !=   >=   <=   <    >
    EQL, NQL, GQL, LQL, LSS, GTR,
    //Other
    INVALID, END
} Type;


//Type enum to string translation array
#define TYPE_COUNT END+1
#define TYPE_LENGTH 15

extern char TypeString[TYPE_COUNT][TYPE_LENGTH];

typedef struct {
    Type        type;       //Enum type of lexeme
    char*       label;      //String label of lexeme
    u8          column;     //Column at which lexeme starts
    u8          row;        //Row at which lexeme starts
} Lexeme;

typedef struct {
    u4              size;
    u4              count;
    Lexeme*         arr;
} LexemeArr;

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row);
void lexeme_deconstruct(Lexeme lexeme);

LexemeArr* lexemearr_create();
void lexemearr_add(LexemeArr* la, Lexeme l);
void lexemearr_remove(LexemeArr* la);

#endif
