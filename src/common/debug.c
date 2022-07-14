#include "debug.h"

static u8 debug_mode;

void g_set_debug_mode(u8 mode)
{
    debug_mode = mode;
}

u8 g_get_debug_mode()
{
    return debug_mode;
}

int g_comp_debug_mode(u8 value)
{
    return (debug_mode & value) != 0;
}

void g_error(char * msg)
{
    printf(COLOR_RED "%s" COLOR_RESET, msg);
}

void g_errorln(char * msg)
{
    printf(COLOR_RED "%s\n" COLOR_RESET, msg);
}

void g_log(char * msg)
{
    printf(COLOR_GREEN "%s" COLOR_RESET, msg);
}

void g_logln(char * msg)
{
    printf(COLOR_GREEN "%s\n" COLOR_RESET, msg);
}
