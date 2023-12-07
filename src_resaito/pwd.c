#include "../inc/minishell.h"

int pwd(t_envval *envval)
{
    t_env   *tmp;

    tmp = envval->env;
    while (ft_strcmp(tmp->key, "PWD") != 0 && tmp->next)
        tmp = tmp->next;
    if (!(tmp->next))
        return (1);
    ft_putendl_fd(tmp->value, STDOUT_FILENO);
    return (0);
}