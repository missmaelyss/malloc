#ifndef _MALLOC_H_
# define _MALLOC_H_

# define NMALLOC 1024
# define MMALLOC 4096
# define NZONE 100 * NMALLOC
# define MZONE 100 * MMALLOC

#include <stdlib.h>
#include <sys/mman.h>

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

struct      s_zone
{
    void    *tiny[4096];
    void    *small[4096];
    void    *large[4096];
};

struct      s_header
{
    char    occuped;
    int     size;
};

extern struct s_zone  g_state;

#endif