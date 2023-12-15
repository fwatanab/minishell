/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_by_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:17:03 by resaito           #+#    #+#             */
/*   Updated: 2023/12/12 12:40:33 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_env	*ft_getpath(t_env *env);

int	child_process(t_node *node, bool has_pipe, t_envval *envval, int pipefd[2])
{
	char	**str;

	if (has_pipe)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (!node->name && ft_getpath(envval->env))
		exit(print_error(node->args[0], "command not found", 127));
	else if (!ft_getpath(envval->env))
		exit(print_error(node->args[0], "No such file or directory", 127));
	if (is_builtin(node))
		exec_builtin(node, envval);
	else
	{
		str = make_env_strs(envval->env);
		execve(node->name, node->args, str);
		str_array_free(str);
		ft_perror(node->name);
	}
	exit(-1);
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

static t_env	*ft_getpath(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && ft_strcmp(tmp->key, "PATH") != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
