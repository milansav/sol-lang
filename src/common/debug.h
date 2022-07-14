#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include "./common.h"

#define NO_OUTPUT               0   //Output absolutely nothing
#define OUTPUT_DEBUG            1   //Warnings, errors etc..
#define OUTPUT_ALL              2   //Output everything
#define OUTPUT_COMPILER         4   //Output from compiler
#define OUTPUT_LEXER            8   //Output from lexer
#define OUTPUT_PARSER           16  //Output from parser
#define OUTPUT_MACRO            32  //Output from preprocessor
#define OUTPUT_LINKER           64  //Output from linker
#define OUTPUT_FILE             128 //Output from file.c

#define COLOR_RED     "\e[31m"
#define COLOR_GREEN   "\e[32m"
#define COLOR_YELLOW  "\e[33m"
#define COLOR_BLUE    "\e[34m"
#define COLOR_MAGENTA "\e[35m"
#define COLOR_CYAN    "\e[36m"
#define COLOR_RESET   "\e[0m"

void g_set_debug_mode(u8 mode);

u8 g_get_debug_mode();

int g_comp_debug_mode(u8 value);

void g_error(char * msg);
void g_errorln(char * msg);
void g_log(char * msg);
void g_logln(char * msg);

#endif
