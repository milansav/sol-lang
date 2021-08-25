#ifndef LEXEME_H
#define LEXEME_H

#include <stdlib.h>
#include "../common/common.h"

#define LA_DEFAULT_SIZE 16 //Default LexemeArr size
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

/*Dynamic array of Lexemes*/
typedef struct {
    u8          size;       //Size in memory
    u8          count;      //Count of elements in array
    Lexeme*     arr;        //Array of lexemes
} LexemeArr;

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row);

LexemeArr* lexemearr_create(void);
void lexemearr_add(LexemeArr* la, Lexeme l);

#endif
