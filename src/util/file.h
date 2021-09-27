#ifndef FILE_H
#define FILE_H

#include "../common/common.h"
#include "../lexer/lexeme.h"
#include "../parser/parser.h"

#include <stdlib.h>

#define DEFAULT_FILEARR_SIZE 4
#define DEFAULT_FILEARR_INCREMENT 4

typedef struct File {
    char*       filename;
    char*       code;
    LexemeArr*  lexemearr;
    Ast*        ast;
} File;

typedef struct FileArr {
    u8          count;
    u8          size;
    File*       arr;
} FileArr;

File file_construct(char* filename);
void file_deconstruct(File file);

FileArr filearr_construct();
void    filearr_add(FileArr* filearr, File file);
void    filearr_deconstruct(FileArr filearr);

#endif