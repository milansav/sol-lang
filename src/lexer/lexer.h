#ifndef LEXER_H
#define LEXER_H

#include "../common/common.h"
#include "lexeme.h"
#include <stdio.h>
#include <string.h>

#define _EOF '\0'

static char* peek(); /*Returns next possible character*/
static char* curr(); /*Returns current possible character*/
static void next(); /*Skips to next possible character*/

LexemeArr* lexer_start(char* code); /*Starts the lexing process on code, returns when _EOF is found*/

static void lexer_skip_comments();

static Lexeme lexer_identifier(); /*Lexes words starting with a-zA-Z characters, if keyword is detected lexer_keyword is called*/
static Lexeme lexer_keyword();
static Lexeme lexer_number();
static Lexeme lexer_string();
static Lexeme lexer_char();
static Lexeme lexer_other(); /*Lexes text starting with misc characters, can call lexer_operator if an operator is detected*/
static Lexeme lexer_operator();

static int is_identifier(char c);
static int is_number(char c);
static int is_operator(char c);
static int is_whitespace(char c);

#endif
