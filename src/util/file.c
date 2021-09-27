#include "file.h"

static char* read_file(char* filename)
{
    char* text;
    FILE* fp = fopen(filename, "r");

    u8 start = ftell(fp);
    fseek(fp, 0, SEEK_END);
    u8 end = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    u8 length = end-start;

    text = malloc(sizeof(char) * length + 1);
    fread(text, length, 1, fp);
    text[length] = '\0';

    fclose(fp);

    return text;
}

File file_construct(char* filename)
{
    File file;
    file.filename = filename; 
    file.code = read_file(file.filename);

    return file;
}

void file_deconstruct(File file)
{
    if(!file.code)
    {
        if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_FILE))
        {
            g_logln("file.c : file_deconstruct: Nothing to deconstruct");
        }
    }
    else
        free(file.code);
    lexemearr_remove(file.lexemearr);
}

FileArr filearr_construct()
{
    FileArr fa;

    fa.count = 0;
    fa.size = DEFAULT_FILEARR_SIZE;
    fa.arr = malloc(sizeof(File) * fa.size);

    return fa;
}

void filearr_add(FileArr* filearr, File file)
{
    if(filearr->count >= filearr->size)
    {
        filearr->size += DEFAULT_FILEARR_INCREMENT;
        filearr->arr = realloc(filearr->arr, filearr->size * sizeof(File));
    }

    filearr->arr[filearr->count] = file;
    filearr->count++;
}

void filearr_deconstruct(FileArr filearr)
{
    if(!filearr.arr)
    {
        if(g_comp_debug_mode(OUTPUT_ALL | OUTPUT_FILE))
        {
            g_logln("file.c : filearr_deconstruct: Nothing to deconstruct");
        }
        return;
    }

    for(u8 i = 0; i < filearr.count; i++)
    {
        file_deconstruct(filearr.arr[i]);
    }

    free(filearr.arr);
}