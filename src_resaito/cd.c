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
	int val;
	t_env *tmp;

	if (node->args[1] == NULL)
		val = chdir(getenv("HOME"));
	else
		val = chdir(node->args[1]);
	if (val < 0)
	{
		perror("cd");
		return (1);
	}
	tmp = env;
	while (tmp->next && ft_strncmp(tmp->key, "PWD", 3) != 0)
		tmp = tmp->next;
	// printf("%s\n", tmp->key);
	free(tmp->value);
	// tmp->value = getcwd();
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
	char	*cd_arg[] = {"cd", "..", NULL};

	node = make_node(N_COMMAND, cd_arg);
	env = new_envs(envp);
	cd(node, env);
	free(node);
	envs_free(env);
}
