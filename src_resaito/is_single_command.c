#include "../inc/minishell.h"

bool    is_single_command(t_node *node)
{
    if (node->type == N_COMMAND)
        return (true);
    return (false);
}