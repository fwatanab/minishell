/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:28:11 by resaito           #+#    #+#             */
/*   Updated: 2023/12/11 12:57:23 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <errno.h>
#include <string.h>

int	input_redir(t_node *node, t_envval *envval)
{
	t_redir	*redir;

	if (node->type == NONE)
		return (0);
	if (node->type == N_PIPE)
	{
		input_redir(node->left, envval);
		input_redir(node->right, envval);
	}
	if (node->type == N_COMMAND)
	{
		redir = node->redir;
		while (redir != NULL)
		{
			if (is_type_heredoc(redir))
				redir->fd = heredoc_exec(redir, envval);
			if (is_type_indirect(redir))
				redir->fd = open(redir->file, O_RDONLY);
			redir = redir->next;
		}
	}
	return (0);
}

int	dup_2_stdin(t_node *node)
{
	t_redir	*redir;

	if (node->redir == NULL)
		return (0);
	redir = node->redir;
	while (redir != NULL)
	{
		if (is_type_heredoc(redir) || is_type_indirect(redir))
		{
			if (!able_read(redir->file))
				return (print_error(redir->file, "Permission denied", 1));
			if (redir->fd == -1)
				return (print_error(redir->file, "No such file or directory",
						1));
			if (redir->fd == -2)
				return (1);
			dup2(redir->fd, STDIN_FILENO);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

bool	is_type_heredoc(t_redir *redir)
{
	if (redir != NULL && redir->type == N_REDIR_HERE)
		return (true);
	return (false);
}

bool	is_type_indirect(t_redir *redir)
{
	if (redir != NULL && redir->type == N_REDIR_IN)
		return (true);
	return (false);
}
