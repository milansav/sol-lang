#ifndef LEXEME_H
#define LEXEME_H

#include "../common/common.h"

typedef enum {
    //Binary ops
    SUM, SUB, MUL, DIV, MOD, ASIGN,
    //Bitwise ops
    AND, OR,
    //Parentheses
    LPAREN, RPAREN, LBRACKET, RBRACKET, LCRLBRACKET, RCRLBRACKET,
    //Deco
    PERIOD, SEMICOLON, COLON, QUERY, QUOTE, SQUOTE,
    //Keywords
    IF, ELSE, FN,
    //Literals
    NUM, STR, CHAR, IDENT,
    //Math
    EQL, NQL, GQL, LQL,
    //Other
    INVALID, END
} Type;

/*Stores data about lexeme*/
typedef struct {
    Type type;              //Enum type of lexeme
    char* label;            //String label of lexeme
    u8 column;              //Column at which lexeme starts
    u8 row;                 //Row at which lexeme starts
} Lexeme;

/*Dynamic array of Lexemes*/
typedef struct {
    u8 size;                //Size in memory
    u8 count;               //Count of elements in array
    Lexeme* arr;            //Array of lexemes
} LexemeArr;

Lexeme lexeme_create(Type type, char* label, u8 col, u8 row);

LexemeArr* lexemearr_create(void);
void lexemearr_add(Lexeme l);

#endif
