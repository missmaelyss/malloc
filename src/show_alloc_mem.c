#include <malloc.h>
#include <stdio.h>

void    show_alloc_mem()
{
    int i;
    printf("TINY:\t%p\n", g_state.tiny);
    i = 0;
    while (g_state.tiny[i] && i < 4096)
    {
        printf("%p\n", g_state.tiny[i]);
        i++;
    }
    printf("SMALL:\t%p\n", g_state.small);
    i = 0;
    while (g_state.small[i] && i < 4096)
    {
        printf("%p\n", g_state.small[i]);
        i++;
    }
    printf("LARGE:\t%p\n", g_state.large);
    i = 0;
    while (g_state.large[i] && i < 4096)
    {
        printf("%p\n", g_state.large[i]);
        i++;
    }
}