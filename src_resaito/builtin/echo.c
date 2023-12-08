/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:07:03 by resaito           #+#    #+#             */
/*   Updated: 2023/12/08 16:52:48 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo(t_node *node)
{
	bool	option;
	size_t	len;

	option = false;
	len = 1;
	if (node->args[1] && ft_strcmp(node->args[1], "-n") == 0)
	{
		option = true;
		len = 2;
	}
	while (node->args[len])
	{
		ft_putstr_fd(node->args[len], STDOUT_FILENO);
		if (node->args[len + 1])
			write(STDOUT_FILENO, " ", 1);
		len++;
	}
	if (!option)
		write(STDOUT_FILENO, "\n", 1);
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
// 	t_node		*node;
// 	char		*echo_arg[] = {"echo", "aaaa", "aaaa", "aaaa", "aaaa",
// 				NULL};

// 	node = make_node(N_COMMAND, echo_arg);
// 	// envval = make_envval(new_envs(envp)); //make_envval.c make_env.c
// 	echo(node);
// 	free(node);
// 	// envs_free(envval->env); //env_free.c ../src/free.c
// 	// free(envval);
// } // ../libft/libft.a
