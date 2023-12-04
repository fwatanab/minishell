#include "../inc/minishell.h"

void    ft_perror(char *str)
{
    perror(str);
    exit(-1);
}