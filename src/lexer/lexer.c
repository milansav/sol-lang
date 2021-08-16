#include "lexer.h"

static char* _code;
static u8 _col;
static u8 _row;

static char* peek()
{
    return _code+1;
}

static char* curr()
{
    return _code;
}

static void next()
{
    _row++;
    _code++;
}

LexemeArr* lexer_start(char* code)
{
    LexemeArr* la = lexemearr_create();
    _code = code;

    while(*curr() != _EOF)
    {
        char _c = *curr();
        while(is_whitespace(_c)) next();
        while(_c == '\n')
        {
            _col++;
            next();
            _row = 0;
        }

        if(_c == '#') lexer_skip_comments();
        
        /*Checking if first character of a word is alphabet but not a number*/
        if(is_identifier(_c) && !is_number(_c)) lexemearr_add(la, lexer_identifier());
        
        if(is_number(_c)) lexemearr_add(la, lexer_number()); 

        next();
    }

    return la;
}

//TBD
static void lexer_skip_comments()
{

}

//TBD
static Lexeme lexer_identifier()
{
    Lexeme l;

    return l;
}

//TBD
static Lexeme lexer_keyword()
{
    Lexeme l;

    return l;
}

//TBD
static Lexeme lexer_number()
{
    Lexeme l;
    
    return l;
}

//TBD
static Lexeme lexer_string()
{
    Lexeme l;

    return l;
}

//TBD
static Lexeme lexer_char()
{
    Lexeme l;

    return l;
}

//TBD
static Lexeme lexer_other()
{
    Lexeme l;

    return l;
}

//TBD
static Lexeme lexer_operator()
{
    Lexeme l;

    return l;
}

static int is_identifier(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static int is_number(char c)
{
    return (c >= '0' && c <= '9') || c == '_' || c == '.';
}

static int is_operator(char c)
{
    return  (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
            c == '=' || c == '<' || c == '>' || c == '!' || c == '^' ||
            c == '&' || c == '|');
}

static int is_whitespace(char c)
{
    return c == '\t' || c == '\r' || c == ' ';
}
