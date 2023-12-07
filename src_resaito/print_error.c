#include "../inc/minishell.h"

int print_error(char *command, char *error, int status)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(command, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd(error, STDERR_FILENO);
    return (status);
}