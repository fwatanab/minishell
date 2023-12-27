/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:28:22 by resaito           #+#    #+#             */
/*   Updated: 2023/12/12 15:07:52 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

static size_t	len_2_equal(char *str);
static void		print_export(t_node *node, t_env *env);
static int		single_export(char *arg, t_envval *envval);

int	export(t_node *node, t_envval *envval)
{
	size_t	size;

	if (!envval)
		return (0);
	if (!envval->env)
		return (0);
	size = 1;
	while (node->args[size] != NULL)
	{
		if (single_export(node->args[size], envval))
			return (1);
		size++;
	}
	print_export(node, envval->env);
	return (0);
}

static size_t	len_2_equal(char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	if (!is_name(str))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identififer", STDERR_FILENO);
		return (0);
	}
	while (str[len] != '\0' && str[len] != '=')
		len++;
	if (str[len] != '=')
		return (0);
	return (len);
}

static void	print_export(t_node *node, t_env *env)
{
	t_env	*tmp;

	if (node->args[1])
		return ;
	tmp = env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		tmp = tmp->next;
	}
}

static int	single_export(char *arg, t_envval *envval)
{
	t_env	*tmp;
	t_env	*new;
	size_t	equal_len;

	equal_len = len_2_equal(arg);
	if (equal_len == 0)
		return (1);
	tmp = envval->env;
	while (tmp->next && ft_strncmp(tmp->key, arg,
			equal_len) != 0)
		tmp = tmp->next;
	if (tmp->key && ft_strncmp(tmp->key, arg, equal_len) == 0)
	{
		free(tmp->value);
		tmp->value = ft_strdup(arg + (equal_len + 1));
	}
	else
	{
		new = new_env(arg);
		if (new == NULL)
			return (1);
		envadd_back(&(envval->env), new);
	}
	return (0);
}

bool	is_name(char *str)
{
	size_t	len;

	len = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (false);
	while (str[len] != '\0' && str[len] != '=')
	{
		if ((!ft_isalnum(str[len])) && str[len] != '_')
			return (false);
		len++;
	}
	return (true);
}

// static int	print_error_export(char *str)
// {
// 	bool	is_error;

// 	is_error = false;
// 	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=')
// 		is_error = true;
// 	if (ft_strchr(str, '$') || ft_strchr(str, '/') || ft_strchr(str, '#')
// 		|| ft_strchr(str, ';'))
// 		is_error = true;
// 	if (!is_error)
// 		return (0);
// 	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
// 	ft_putstr_fd(str, STDERR_FILENO);
// 	ft_putendl_fd("': not a valid identififer", STDERR_FILENO);
// 	return (1);
// }

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
// 	t_envval	*envval;
//     char    **array;
//     int     size = 0;

// 	node = make_node(N_COMMAND, export_arg);
// 	envval = make_envval(new_envs(envp));
// 	export(node, envval);
//     // array = make_env_strs(envval->env);
//     envs_free(envval->env); // envs_free.c
// 	free(envval);
//     // while (array[size] != NULL)
//     // {
//     //     printf("%s\n", array[size]);
//     //     size++;
//     // }
// 	free(node);
//     // str_array_free(array);
// 	// envs_str_free(env, array);
// }

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
