#include <stdio.h> // pour printf
#include <malloc.h>

void    *malloc(size_t size)
{
    void    *map;
    int     n;
    int     i;
    int     space;  

    n = 0;
    i = sizeof(int);
    space = 0;
    while (g_state.tiny[n]) {
        while (i < NZONE && i < *(int *)g_state.tiny[n]) {
            printf("%d < %d\n%d\n", i, *(int *)g_state.tiny[n]), ((struct s_header)*((struct s_header *)g_state.tiny[n] + i)).size;
            i += sizeof(struct s_header) + (((struct s_header *)g_state.tiny[n] + sizeof(int)))->size;
        }
        if (i + size + sizeof(struct s_header) < NZONE) {
            space = 1;
            break;
        }
        i = 0;
        n++;
    }
    printf("size = %d, space = %d, n = %d, i = %d\n", size, space, n, i);
    if (space == 0) {
        g_state.tiny[n] = mmap(NULL, NZONE, PROT_READ|PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        *(int *)g_state.tiny[n] = sizeof(int) + sizeof(struct s_header) + size;
        *((struct s_header *)g_state.tiny[n] + sizeof(int)) = (struct s_header){1, size};
        printf("%d %d %d\n", sizeof(int), sizeof(struct s_header), size);
        printf("%d \n", (((struct s_header *)g_state.tiny[n] + sizeof(int)))->size);
        // ((int *)g_state.tiny[n])[i] = size;
        // ((char *)g_state.tiny[n])[i * (sizeof(int) / sizeof(char)) + 1] = 1;
        // printf("%d, %c\n", ((int *)g_state.tiny[n])[i], ((char *)g_state.tiny[n])[i * (sizeof(int) / sizeof(char)) + 1]);
        return (((char *)g_state.tiny[n] + sizeof(int) + sizeof(struct s_header)));
    }
    else {
        *((struct s_header *)g_state.tiny[n] + i) = (struct s_header){size, 1};
        printf("%d, %c\n", ((int *)g_state.tiny[n])[i], ((char *)g_state.tiny[n])[i * (sizeof(int) / sizeof(char)) + 1]);
        return (&(((char *)g_state.tiny[n])[i + 1]));
    }
}

//     printf("n = %d, i = %d\n", n, i);
//     if (n == -1) {
//         n++;
//         g_state.tiny[n] = mmap(NULL, NZONE, PROT_READ|PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
//         ((int *)g_state.tiny[n])[0] = 1;
//         ((int *)g_state.tiny[n])[1] = size;
//         return (&(((int *)g_state.tiny[n])[2]));
//     }
//     i = 0;
//     // if (n > 0) {
//     while (i < NZONE && ((int *)g_state.tiny[n])[i]) {
//         printf("%d\n", ((int *)g_state.tiny[n])[i]);
//         i++;
//     }
//     printf("i = %d\n", i);
//     // }
//     if (i + size >= NZONE)
//         g_state.tiny[n + 1] = mmap(NULL, NZONE, PROT_READ|PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

//     // i = 0;
//     // while (n > 0 && ((char*)g_state.tiny[n - 1])[i] != 0) {
//     //     i++;
//     // }

//     // ((char*)g_state.tiny[n - 1])[i] = ;
    

//     if (map == MAP_FAILED) {
//         exit(EXIT_FAILURE);
//     }

//     return (map);
// }