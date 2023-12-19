/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:09:13 by resaito           #+#    #+#             */
/*   Updated: 2023/12/19 12:14:32 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <errno.h>
#include <string.h>

int	output_redir(t_node *node, t_envval *envval)
{
	t_redir	*redir;

	if (node->type == NONE)
		return (0);
	if (node->type == N_PIPE)
	{
		output_redir(node->left, envval);
		output_redir(node->right, envval);
	}
	if (node->type == N_COMMAND)
	{
		redir = node->redir;
		while (redir != NULL)
		{
			if (is_type_redirect(redir))
				redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC
						| O_CLOEXEC, S_IRUSR | S_IWUSR);
			if (is_type_append(redir))
				redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND
						| O_CLOEXEC, S_IRUSR | S_IWUSR);
			redir = redir->next;
		}
	}
	return (0);
}

int	dup_2_stdout(t_node *node)
{
	t_redir	*redir;

	if (node->redir == NULL)
		return (0);
	redir = node->redir;
	while (redir != NULL)
	{
		if (is_type_redirect(redir) || is_type_append(redir))
		{
			if (!able_write(redir->file))
				return (print_error(redir->file, "Permission denied", 1));
			if (redir->fd == -1)
				return (print_error(redir->file, "No such file or directory",
						1));
			dup2(redir->fd, STDOUT_FILENO);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

bool	is_type_redirect(t_redir *redir)
{
	if (redir != NULL && redir->type == N_REDIR_OUT)
		return (true);
	return (false);
}

bool	is_type_append(t_redir *redir)
{
	if (redir != NULL && redir->type == N_REDIR_APPEND)
		return (true);
	return (false);
}
