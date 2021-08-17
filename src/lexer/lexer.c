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
        while(_c == '\n')
        {
            _col++;
            next();
            _row = 0;
        }

        while(is_whitespace(*peek())) next();

        if(_c == '#')   lexer_skip_comments();
        if(_c == '"')   lexemearr_add(la, lexer_string());
        if(_c == '\'')  lexemearr_add(la, lexer_char());

        /*Checking if first character of a word is alphabet but not a number*/
        if(is_identifier(_c) && !is_number(_c)) lexemearr_add(la, lexer_identifier());       
        if(is_number(_c)) lexemearr_add(la, lexer_number()); 
        if(is_operator(_c)) lexemearr_add(la, lexer_operator());
        
        next();
    }

    return la;
}

static void lexer_skip_comments()
{
    while(*curr() != '\n') next();
    next();
    _col++;
    _row = 0;
}

//TBD set l.type
static Lexeme lexer_identifier()
{
    Lexeme l;
    char* start     = curr();
    
    while(is_identifier(*curr())) next();

    char* end       = curr();
    u8 length       = end-start;

    char* label     = malloc(length+1);
    label[length]   = 0;
    
    strncpy(label, start, length);

    //TODO: if the label is a keyword, return lexer_keyword()
    l = lexeme_create(IDENT, label, _col, _row);

     //printf("Lexeme Identifier: .%s.\n", l.label);

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
    char* start     = curr();
    
    while(is_number(*curr())) next();

    char* end       = curr();
    u8 length       = end-start;

    char* label     = malloc(length+1);
    label[length]   = 0;

    strncpy(label, start, length);    

    l = lexeme_create(NUM, label, _col, _row);

    //printf("Lexeme Number: .%s.\n", l.label);

    return l;
}

//TBD
static Lexeme lexer_string()
{
    Lexeme l;
    
    next(); //Skip first "

    char* start     = curr();

    while(*curr() != '"') next();

    char* end       = curr();
    u8 length       = end-start;

    char* label     = malloc(length+1);
    label[length]   = 0;

    strncpy(label, start, length);

    l = lexeme_create(STR, label, _col, _row);

    next(); //Skip last "

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
