/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:24:50 by resaito           #+#    #+#             */
/*   Updated: 2023/12/08 15:55:22 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_envval *envval)
{
	char	**str;
	size_t	len;

	if (!(envval->env))
		return (1);
	str = make_env_strs(envval->env);
	len = 0;
	while (str[len])
	{
		printf("%s\n", str[len]);
		len++;
	}
    str_array_free(str);
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

// int	main(int ac, char **av, char **envp)
// {
// 	// t_node		*node;
// 	t_envval	*envval;
// 	// char		*env_arg[] = {"env", NULL};

// 	// node = make_node(N_COMMAND, env_arg);
// 	envval = make_envval(new_envs(envp)); //make_envval.c make_env.c
// 	ft_env(envval);
// 	// free(node);
// 	envs_free(envval->env); //env_free.c ../src/free.c
// 	free(envval);
// } // ../libft/libft.a

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
