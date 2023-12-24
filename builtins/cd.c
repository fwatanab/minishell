/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:14:59 by resaito           #+#    #+#             */
/*   Updated: 2023/12/24 18:06:16 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

#define PATHNAME_SIZE 512

int	cd(t_node *node, t_envval *envval)
{
	int		val;
	t_env	*tmp;
	char	pathname[PATHNAME_SIZE];

	if (node->args[1] == NULL)
		val = chdir(getenv("HOME"));
	else
		val = chdir(node->args[1]);
	if (val < 0)
	{
		perror("cd");
		return (1);
	}
	tmp = envval->env;
	ft_memset(pathname, '\0', PATHNAME_SIZE);
	while (tmp->next && ft_strcmp(tmp->key, "PWD") != 0)
		tmp = tmp->next;
	if (getcwd(pathname, PATHNAME_SIZE) == NULL)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(pathname);
	return (0);
}

// t_node	*make_node(enum e_type node_type, char **args)
// {
// 	t_node	*node;

// 	node = calloc(sizeof(t_node), 1);
// 	node->type = node_type;
// 	node->name = args[0];
// 	node->args = args;
// 	return (node);
// }

// int pwd(t_node *node, t_envval *envval);

// int	main(int ac, char **av, char **envp)
// {
// 	t_node		*node;
// 	t_node		*pwd_node;
// 	t_envval	*envval;
// 	char		*cd_arg[] = {"cd", NULL};
// 	char		*pwd_arg[] = {"pwd", NULL};

// 	node = make_node(N_COMMAND, cd_arg);
// 	pwd_node = make_node(N_COMMAND, pwd_arg);
// 	envval = make_envval(new_envs(envp)); //make_envval.c make_env.c
// 	cd(node, envval);
// 	pwd(pwd_node, envval);
// 	free(node);
// 	free(pwd_node);
// 	envs_free(envval->env); //env_free.c ../src/free.c
// 	free(envval);
// } // ../libft/libft.a
