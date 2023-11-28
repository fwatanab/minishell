#include "../inc/minishell.h"

int content_node(t_node *node)
{
    if (node->type == NONE)
        return (0);
    if (node->type == N_PIPE)
    {
        content_node(node->left);
        content_node(node->right);
    }
    if (node->type == N_COMMAND)
    {
        if (is_type_heredoc(node->redir))
            node->redir->input_fd = heredoc_exec(node);
    }
    return (0);
}

bool    is_type_heredoc(t_redir *redir)
{
    if (redir != NULL && redir->type == N_REDIR_HERE)
        return (true);
    return (false);
}
