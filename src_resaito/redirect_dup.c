/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/11/13 16:42:53 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	redir_dup(t_node *node, int *pipefd)
{
	if (node->redir != NULL && (node->redir->type == N_REDIR_OUT
			|| node->redir->type == N_REDIR_APPEND))
	{
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
	}
	return (0);
}

int	indirect_exec(t_node *node)
{
	int		stdin_fd;
	char	*file;

	stdin_fd = 0;
	stdin_fd = open(file, O_RDONLY);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	execve(node->name, node->args, NULL);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	return (0);
}
