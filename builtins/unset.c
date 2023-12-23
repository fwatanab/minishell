/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:27:05 by resaito           #+#    #+#             */
/*   Updated: 2023/12/11 18:53:09 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

static void	remove_env_entry(t_env **env, t_env *prev, t_env *current);
static bool	is_equal_in_args(char *args);
static int	unset_error_print(char *args);
static int	unset_single(char *name, t_envval *envval);

int	unset(t_node *node, t_envval *envval)
{
	size_t	size;

	size = 1;
	while (node->args[size] != NULL)
	{
		if (is_equal_in_args(node->args[size]))
			return (unset_error_print(node->args[size]));
		unset_single(node->args[size], envval);
		size++;
	}
	return (0);
}

static void	remove_env_entry(t_env **env, t_env *prev, t_env *current)
{
	if (current == *env)
		*env = current->next;
	else
		prev->next = current->next;
}

static bool	is_equal_in_args(char *args)
{
	if (ft_strchr(args, '=') == NULL)
		return (false);
	return (true);
}

static int	unset_error_print(char *args)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd("': not a valid identififer", STDERR_FILENO);
	return (1);
}

static int	unset_single(char *name, t_envval *envval)
{
	t_env	*tmp;
	t_env	*tmp_back;

	tmp = envval->env;
	tmp_back = tmp;
	while (tmp && ft_strcmp(name, tmp->key) != 0 && tmp->next)
	{
		tmp_back = tmp;
		tmp = tmp->next;
	}
	if (tmp->next)
		remove_env_entry(&(envval->env), tmp_back, tmp);
	else if (ft_strcmp(tmp->key, tmp_back->key) == 0)
		envval->env = NULL;
	else if (ft_strcmp(name, tmp->key) == 0)
		tmp_back->next = NULL;
	env_free(tmp);
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
// 	t_node	*node;
// 	t_node	*node2;
// 	// t_env	*env;
//     t_envval *envval;
//     char    **array;
//     int     size = 0;
// 	char	*unset_arg[] = {"unset", "aaa", NULL};
// 	char	*args[] = {"aaa=hoge", "hoge=fuga", NULL};
// 	char	*unset_arg2[] = {"unset", "hoge", NULL};

// 	node = make_node(N_COMMAND, unset_arg);
// 	node2 = make_node(N_COMMAND, unset_arg2);
// 	envval = make_envval(new_envs(args)); //make_envval.c make_env.c
// 	unset(node, envval);
// 	unset(node2, envval);
// 	// printf("%d\n",unset(node, envval));
//     array = make_env_strs(envval->env); //make_env.c
// 	if (array == NULL)
// 	{
// 		printf("array == NULL\n");
// 		exit(1);
// 	}
//     envs_free(envval->env); // env_free.c
//     free(envval);
//     while (array[size] != NULL)
//     {
//         printf("%s\n", array[size]);
//         size++;
//     }
// 	free(node);
// 	free(node2);
//     str_array_free(array); //env_free.c ../src/free.c
// 	// envs_str_free(env, array);
// } // ../libft/libft.a

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
