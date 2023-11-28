#include "../inc/minishell.h"
#include <string.h>
#include <errno.h>

int content_node(t_node *node)
{
    t_redir *redir;

    if (node->type == NONE)
        return (0);
    if (node->type == N_PIPE)
    {
        content_node(node->left);
        content_node(node->right);
    }
    if (node->type == N_COMMAND)
    {
        redir = node->redir;
        while (redir != NULL)
        {
            if (is_type_heredoc(redir))
                redir->fd = heredoc_exec(redir);
            if (is_type_indirect(redir))
                redir->fd = open(redir->file[0], O_RDONLY);
            redir = redir->next;
        }
    }
    return (0);
}

bool    is_type_heredoc(t_redir *redir)
{
    if (redir != NULL && redir->type == N_REDIR_HERE)
        return (true);
    return (false);
}

bool    is_type_indirect(t_redir *redir)
{
    if (redir != NULL && redir->type == N_REDIR_IN)
        return (true);
    return (false);
}
