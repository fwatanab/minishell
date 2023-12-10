/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:27:05 by resaito           #+#    #+#             */
/*   Updated: 2023/12/08 16:09:00 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void remove_env_entry(t_env **env, t_env *prev, t_env *current);

int	unset(t_node *node, t_envval *envval)
{
	size_t	size;
	t_env	*tmp;
	t_env	*tmp_back;

	size = 1;
	while (node->args[size] != NULL)
	{
		tmp = envval->env;
		tmp_back = tmp;
		while (ft_strcmp(node->args[size], tmp->key) != 0 && tmp->next)
		{
			tmp_back = tmp;
			tmp = tmp->next;
		}
		if (tmp->next)
			remove_env_entry(&(envval->env), tmp_back, tmp);
		else if (ft_strcmp(node->args[size], tmp->key) == 0)
			tmp_back->next = NULL;
		else
			return (1);
		env_free(tmp);
		size++;
	}
	return (0);
}

static void remove_env_entry(t_env **env, t_env *prev, t_env *current)
{
    if (current == *env)
        *env = current->next;
    else
        prev->next = current->next;
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
// 	t_node	*node;
// 	// t_env	*env;
//     t_envval *envval;
//     char    **array;
//     int     size = 0;
// 	char	*unset_arg[] = {"export", "$PATH", NULL};

// 	node = make_node(N_COMMAND, unset_arg);
// 	envval = make_envval(new_envs(envp)); //make_envval.c make_env.c
// 	printf("%d\n",unset(node, envval));
//     array = make_env_strs(envval->env); //make_env.c
//     envs_free(envval->env); // env_free.c
//     free(envval);
//     while (array[size] != NULL)
//     {
//         printf("%s\n", array[size]);
//         size++;
//     }
// 	free(node);
//     str_array_free(array); //env_free.c ../src/free.c
// 	// envs_str_free(env, array);
// } // ../libft/libft.a

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
