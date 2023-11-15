/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/11/15 14:39:14 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	redir_dup(t_node *node, int *pipefd)
{
	if (!(node->redir != NULL && (node->redir->type == N_REDIR_OUT
				|| node->redir->type == N_REDIR_APPEND)))
		return (0);
	close(pipefd[0]);
	while (node->redir != NULL && (node->redir->type == N_REDIR_OUT
			|| node->redir->type == N_REDIR_APPEND))
	{
		if (node->redir->type == N_REDIR_OUT)
			pipefd[1] = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else
			pipefd[1] = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		node->redir = node->redir->next;
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	return (0);
}

int	indirect_exec(t_node *node, int dupout)
{
	if (!(node->redir != NULL && node->redir->type == N_REDIR_IN))
		return (0);
	while (node->redir != NULL && (node->redir->type == N_REDIR_IN))
	{
		if (node->redir->type == N_REDIR_IN)
			dupout = open(node->redir->file[0], O_RDONLY);
		node->redir = node->redir->next;
	}
	dup2(dupout, STDIN_FILENO);
	close(dupout);
	return (0);
}
