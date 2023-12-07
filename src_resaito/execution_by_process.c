/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_by_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:17:03 by resaito           #+#    #+#             */
/*   Updated: 2023/12/04 14:17:14 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int child_process(t_node *node, bool has_pipe, t_envval *envval,
		int pipefd[2])
{
	if (has_pipe)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	redir_dup(node);
    if (!node->name)
        exit(print_error(node->args[0], "command not found", 127));
	execve(node->name, node->args, make_env_strs(envval->env));
	ft_perror(node->name);
    return (0);
}

void	parent_process(bool has_pipe, int pipefd[2])
{
	if (has_pipe)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}