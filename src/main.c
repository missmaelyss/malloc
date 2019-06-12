#include <malloc.h>

#include <stdio.h> // pour printf
#include <errno.h>
#include <string.h>

int sz;

int main ()
{
    char    *ptr;
    int     i;
    
    // g_state.tiny[0] =  mmap(NULL, NZONE, PROT_READ|PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    malloc(10);
    malloc(2000);
    malloc(400000000);
    show_alloc_mem();
    return (0);
}