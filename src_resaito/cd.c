/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:14:59 by resaito           #+#    #+#             */
/*   Updated: 2023/12/04 17:54:06 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cd(t_node *node, t_env *env)
{
	char	*str;
	t_env	*tmp;

	if (ft_strncmp(node->args[1], "/", 1) == 0)
		str = node->args[1];
	else
	{
		tmp = env;
		if (ft_strncmp(node->args[1], "./", 2) == 0)
			str = ft_strjoin(getenv("PWD"), node->args[1] + 2);
		else if (ft_strncmp(node->args[1], "..", 2) == 0)
			str = ft_strndup(getenv("PWD"), ft_strrchr(getenv("PWD"), '/')
					- getenv("PWD"));
	}
	return (0);
}

t_node	*make_node(enum e_type node_type, char **args)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->type = node_type;
	node->name = args[0];
	node->args = args;
	return (node);
}

int	main(int ac, char **av, char **envp)
{
	t_node	*node;
	t_env	*env;
	char	*cd_arg[] = {"cd", "../src", NULL};

	node = make_node(N_COMMAND, cd_arg);
	env = new_envs(envp);
	cd(node, env);
}
