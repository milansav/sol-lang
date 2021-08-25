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

static void new_line()
{
    _col = 0;
    _row++;
    next();
}

static void next()
{
    _col++;
    _code++;
}

LexemeArr* lexer_start(char* code)
{
    LexemeArr* la = lexemearr_create();
    _code = code;
    
    while(*curr() != '\0')
    {

        if(*curr() == '\n')
        {
            new_line();
            continue;
        }

        if(is_whitespace(*curr()))
        {
            next();
            continue;
        }

        if(is_identifier(*curr()) && !is_number(*curr()))
        {
            lexemearr_add(la, lexer_identifier());
            continue;
        }
        else if(is_number(*curr()))
        {
            lexemearr_add(la, lexer_number());
            continue;
        }
        else if(is_operator(*curr()))
        {
            lexemearr_add(la, lexer_operator());
            continue;
        }
        else if(*curr() == '"')
        {
            lexemearr_add(la, lexer_string());
            continue;
        }
        else if(*curr() == '\'')
        {
            lexemearr_add(la, lexer_char());
            continue;
        }
        else if(*curr() == '#')
        {
            lexer_skip_comments();
            continue;
        }
        else
        {
            lexemearr_add(la, lexer_other());
            continue;
        }
    }

    lexemearr_add(la, lexeme_create(END, "", -1, -1));

    return la;
}

//TODO: distinguish different keyword types
static Lexeme lexer_identifier()
{
    Lexeme l;

    char* start = curr();

    while(is_identifier(*curr())) next();

    char* end = curr();
    u8 length = end-start;

    char* label = malloc(length+1);
    label[length] = 0;

    strncpy(label, start, length);

    l = lexeme_create(IDENT, label, _col, _row);

    l = lexer_keyword(l);

    return l;
}

static Lexeme lexer_keyword(Lexeme l)
{
    int i = IF; //IF is a starting point for keywords in keywords enum (lexeme.h)
    for(i = 0; i < KEYWORDS_COUNT; i++)
    {
        if(!strcmp(l.label, keywords[i]))
        {
            l.type = i;
            break;
        } 
    }

    return l;
}
static Lexeme lexer_number()
{
    Lexeme l;

    char* start = curr();

    while(is_number(*curr())) next();

    char* end = curr();
    u8 length = end-start; 

    char* label = malloc(length+1);
    label[length] = 0;

    strncpy(label, start, length);

    l = lexeme_create(NUM, label, _col, _row);

    return l;
}

//TODO: distinguish different operator types
static Lexeme lexer_operator()
{
    Lexeme l;

    char* start = curr();

    while(is_operator(*curr())) next();

    char* end = curr();
    u8 length = end-start;

    char* label = malloc(length+1);
    label[length] = 0;

    strncpy(label, start, length);

    l = lexeme_create(SUM, label, _col, _row);

    return l;
}

static Lexeme lexer_char()
{
    Lexeme l;

    next(); //Skip initial '

    char* start = curr();

    while(*curr() != '\'') next();

    char* end = curr();
    u8 length = end-start; 

    char* label = malloc(length+1);
    label[length] = 0;
    
    strncpy(label, start, length);

    if(length > 1)
    {
        l = lexeme_create(INVALID, label, _col, _row);
        return l;
    }

    l = lexeme_create(CHAR, label, _col, _row);

    next(); //Skip final '

    return l;
}

static Lexeme lexer_string()
{
    Lexeme l;

    next(); //Skip initial "

    char* start = curr();

    while(*curr() != '"') next();

    char* end = curr();
    u8 length = end-start;

    char* label = malloc(length+1);
    label[length] = 0;

    strncpy(label, start, length);

    l = lexeme_create(STR, label, _col, _row);

    next(); //Skip final "

    return l;
}

static Lexeme lexer_other()
{
    Lexeme l;

    char c = *curr();
    char* start = curr();
    char* label = malloc(2);
    label[1] = '\0';
    strncpy(label, start, 1);
    
    switch(c)
    {
        case '(':
            l = lexeme_create(LPAREN, label, _col, _row);
            break;
        case ')':
            l = lexeme_create(RPAREN, label, _col, _row);
            break;
        case '{':
            l = lexeme_create(LCRLBRACKET, label, _col, _row);
            break;
        case '}':
            l = lexeme_create(RCRLBRACKET, label, _col, _row);
            break;
        case '[':
            l = lexeme_create(LBRACKET, label, _col, _row);
            break;
        case ']':
            l = lexeme_create(RBRACKET, label, _col, _row);
            break;
        case '.':
            l = lexeme_create(PERIOD, label, _col, _row);
            break;
        case ':':
            l = lexeme_create(COLON, label, _col, _row);
            break;
        case ';':
            l = lexeme_create(SEMICOLON, label, _col, _row);
            break;
        case '?':
            l = lexeme_create(QUERY, label, _col, _row);
            break;
    }

    next();

    return l;
}

static void lexer_skip_comments()
{
    while(*curr() != '\n') next();
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
