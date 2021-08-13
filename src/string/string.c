#include "string.h"
#include <string.h>
#include <stdlib.h>

static char temp[1000];

StringPool* stringpool_create(void)
{
    StringPool* sp  = malloc(sizeof(StringPool));
    sp->size        = SP_DEFAULT_SIZE+1;
    sp->data        = malloc(sp->size+1);
    sp->length      = 0;
    memset(sp->data, 0, sp->size+1);
    return sp;
}

void stringpool_clean(StringPool* sp)
{
    free(sp->data);
    free(sp);
}

void stringpool_data_append(StringPool* sp, char* c)
{
    unsigned long c_len = strlen(c);

    if(sp->length + c_len >= sp->size)
    {
        sp->size += SP_INCREASE_SIZE;
        sp->data = realloc(sp->data, sp->size);
    }

    strcat(sp->data, c);
    sp->length += c_len;
}

String* string_create(StringPool* sp, char* start, char* end)
{
    String* s   = malloc(sizeof(String));
    s->length   = end-start;
    s->start    = start;
    s->end      = end;
    s->sp       = sp;
    return s;
}

void string_clean(String* s)
{
    free(s);
}

char* string_read(String* s)
{
    temp[s->length] = '\0';
    return strncpy(temp, s->start, s->length);
}

StringArr* stringarr_create(void)
{
    StringArr* sa   = malloc(sizeof(StringArr));
    sa->size        = SA_DEFAULT_SIZE;
    sa->count       = 0;
    sa->data        = malloc(sizeof(String)*sa->size);
    return sa;
}

void stringarr_clean(StringArr* sa)
{
    for(unsigned long i = 0; i < sa->count; i++)
    {
        string_clean(&sa->data[i]);
    }

    free(sa);
}

void stringarr_add(StringArr* sa, String* s)
{
    if(sa->count + 1 >= sa->size)
    {
        sa->size += SA_INCREASE_SIZE;
        sa->data = realloc(sa->data, sa->size);
    }

    sa->data[sa->count] = *s;
    sa->count++;
}
