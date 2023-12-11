/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:32:35 by resaito           #+#    #+#             */
/*   Updated: 2023/12/11 19:06:30 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(t_node *node)
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

void	exec_builtin(t_node *node, t_envval *envval)
{
	if (ft_strcmp(node->args[0], "echo") == 0)
		envval->status = echo(node);
	else if (ft_strcmp(node->args[0], "cd") == 0)
		envval->status = cd(node, envval);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		envval->status = pwd(envval);
	else if (ft_strcmp(node->args[0], "export") == 0)
		envval->status = export(node, envval);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		envval->status = unset(node, envval);
	else if (ft_strcmp(node->args[0], "env") == 0)
		envval->status = ft_env(envval);
	 else if (ft_strcmp(node->args[0], "exit") == 0)
		ft_exit(node, envval);
}
