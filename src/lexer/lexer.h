#ifndef LEXER_H
#define LEXER_H

#include "../common/common.h"
#include "../common/keywords.h"
#include "lexeme.h"
#include <stdio.h>
#include <string.h>

#define _EOF '\0'

LexemeArr* lexer_start(char* code);

#endif
