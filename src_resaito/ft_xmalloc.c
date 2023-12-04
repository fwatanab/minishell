#include "../inc/minishell.h"

void *ft_xmalloc(size_t size)
{
    void *res;

    res = malloc(size);
    if (res == NULL)
        exit(1);
    return (res);
}