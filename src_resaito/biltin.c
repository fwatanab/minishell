#include "../inc/minishell.h"

bool    is_biltin(t_node *node)
{
    if (ft_strcmp(node->args[0], "echo") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "cd") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "export") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "unset") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "env") == 0)
        return (true);
    else if (ft_strcmp(node->args[0], "exit") == 0)
        return (true);
    else
        return (false);
}

void    exec_biltin(t_node *node, t_envval *envval)
{
    if (ft_strcmp(node->args[0], "echo") == 0)
        envval->status = echo(node, envval);
    else if (ft_strcmp(node->args[0], "cd") == 0)
        envval->status = cd(node, envval);
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        envval->status = pwd(envval);
    else if (ft_strcmp(node->args[0], "export") == 0)
        envval->status = export(node, envval);
    else if (ft_strcmp(node->args[0], "unset") == 0)
        envval->status = unset(node, envval);
    else if (ft_strcmp(node->args[0], "env") == 0)
        envval->status = env(node, envval);
    else if (ft_strcmp(node->args[0], "exit") == 0)
        envval->status = exit(node, envval);
}