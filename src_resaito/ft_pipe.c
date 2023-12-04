#include "../inc/minishell.h"

int ft_pipe(int pipefd[2])
{
    if (pipe(pipefd) < 0)
        ft_perror("pipe");
    return (0);
}