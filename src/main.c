#include "./lexer/lexer.h"
#include "./lexer/lexeme.h"
#include "./common/debug.h"
#include "./common/common.h"
#include "./parser/parser.h"
#include "./util/file.h"

#include <stdio.h>
#include <string.h>
#include <stdio.h>

void init();
void load_args(int argc, char* argv[]);
void output_argument(char* option);
void cleanup();

FileArr files;

int main(int argc, char* argv[])
{
    init();
    atexit(cleanup);

    load_args(argc, argv);

    for(u8 i = 0; i < files.count; i++)
    {
        files.arr[i].lexemearr  = lexer_start(files.arr[i].code);
        files.arr[i].ast        = parser_start(files.arr[i].lexemearr);
    }

    return 0;
}


void init()
{
    g_set_debug_mode(OUTPUT_DEBUG);
    files = filearr_construct();
}

void load_args(int argc, char* argv[])
{
    for(u8 i = 1; i < argc; i++)
    {

        if(argv[i][0] == '-')
        {
            if(argv[i][1] == 'W')
            {
                output_argument(argv[i]);
            }
            else if(argv[i][1] == 'c')
            {
                if(!argv[i+1])
                {
                    g_errorln("No argument specified for option -c");
                    exit(1);
                }
                i++;
                while(i < argc)
                {
                    if(argv[i+1][0] == '-')
                        break;
                    File f = file_construct(argv[i]);
                    filearr_add(&files, f);
                    i++;
                    continue;
                }
            }
        }
    }
}

void output_argument(char* option)
{
    if(!strcmp((option+2), "all"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_ALL);
    else if(!strcmp((option+2), "compiler"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_COMPILER);
    else if(!strcmp((option+2), "lexer"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_LEXER);
    else if(!strcmp((option+2), "parser"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_PARSER);
    else if(!strcmp((option+2), "macro"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_MACRO);
    else if(!strcmp((option+2), "linker"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_LINKER);
    else if(!strcmp((option+2), "file"))
        g_set_debug_mode(g_get_debug_mode()+OUTPUT_FILE);
    else if(!strcmp((option+2), "none"))
    {
        g_set_debug_mode(NO_OUTPUT);
    }
    else
    {
        g_error("Unknown output argument: ");
        printf("%s " COLOR_RED "!\n" COLOR_RESET, option);
        exit(0);
    }

}


void cleanup()
{
    filearr_deconstruct(files);
}