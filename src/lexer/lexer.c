#include "lexer.h"

//TODO: Update lexeme column and row counting (currenctly lexemes positions are marked at the end of the lexeme instead of the start)

static char* _code;
static u8 _col;
static u8 _row;

static char* peek(); /*Returns next possible character*/
static char* curr(); /*Returns current possible character*/
static void next(); /*Skips to next possible character*/
static void new_line(); /*Resets col, increments row, and goes to next character*/

static void lexer_skip_comments(); /*It just skips comments*/
static void lexer_new_line(); /*Loops checking for \n, calls new_line everytime \n is found*/

static Lexeme lexer_identifier(); /*Lexes words starting with a-zA-Z characters, if keyword is detected lexer_keyword is called*/
static Lexeme lexer_keyword(Lexeme l); /*Takes identifier lexeme as input, if the lexeme isn't a keyword, returns the same lexeme, otherwise it changes its properties'*/
static Lexeme lexer_number();
static Lexeme lexer_string();
static Lexeme lexer_char();
static Lexeme lexer_other(); /*Lexes text starting with misc characters, can call lexer_operator if an operator is detected*/
static Lexeme lexer_operator();
static Lexeme lexer_other();

static int is_identifier(char c);
static int is_number(char c);
static int is_operator(char c);
static int is_whitespace(char c);

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
    _row = 0;
    _col = 0;
    
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

    lexemearr_add(la, lexeme_create(END, "End", -1, -1));

    return la;
}

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
    for(i; i < NUM; i++) //NUM is ending point for keywords in keywords enum
    {
        if(!strcmp(l.label, keywords[i-IF])) //i needs to be normalized for access in keywords
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

    switch(label[0])
    {
        case '+':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '+':
                        l = lexeme_create(INC, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }

            l = lexeme_create(SUM, label, _col, _row);
            return l;

            break;
        case '-':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '-':
                        l = lexeme_create(DEC, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }

            l = lexeme_create(SUB, label, _col, _row);
            return l;

            break;
        case '*':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '*':
                        l = lexeme_create(POW, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }
            
            l = lexeme_create(MUL, label, _col, _row);
            return l;

            break;
        case '/':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '/':
                        l = lexeme_create(DIVT, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }

            l = lexeme_create(DIV, label, _col, _row);
            return l;

            break;
        case '=':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '=':
                        l = lexeme_create(EQL, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }

            l = lexeme_create(ASSIGN, label, _col, _row);
            return l;

            break;
        case '!':
            if(length > 1)
            {
                switch(label[1])
                {
                    case '=':
                        l = lexeme_create(NQL, label, _col, _row);
                        return l;
                        break;
                    default:
                        l = lexeme_create(INVALID, label, _col, _row);
                        return l;
                        break;
                }
            }
            
            l = lexeme_create(NOT, label, _col, _row);
            return l;

            break;
        case '^':
            if(length > 1)
            {
                l = lexeme_create(INVALID, label, _col, _row);
                return l;
            }

            l = lexeme_create(POW, label, _col, _row);
            return l;

            break;
        case '&':
            if(length > 1)
            {
                l = lexeme_create(INVALID, label, _col, _row);
                return l;
            }

            l = lexeme_create(AND, label, _col, _row);
            return l;

            break;
        case '|':
            if(length > 1)
            {
                l = lexeme_create(INVALID, label, _col, _row);
                return l;
            }

            l = lexeme_create(OR, label, _col, _row);
            return l;

            break;
        case '~':
            if(length > 1)
            {
                l = lexeme_create(INVALID, label, _col, _row);
                return l;
            }

            l = lexeme_create(XOR, label, _col, _row);
            return l;

            break;

    }

    l = lexeme_create(INVALID, label, _col, _row);

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
        case ',':
            l = lexeme_create(COMMA, label, _col, _row);
            break;
        default:
            l = lexeme_create(INVALID, label, _col, _row);
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
