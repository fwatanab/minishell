/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:12:57 by resaito           #+#    #+#             */
/*   Updated: 2023/12/01 15:24:03 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*new_envs(char **envp)
{
	t_env	*env;
	size_t	size;

	size = 0;
	env = NULL;
	while (envp[size] != NULL)
	{
		envadd_back(&env, new_env(envp[size]));
		size++;
	}
	return (env);
}

void	envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*new_env(char *envp)
{
	t_env	*new;
	size_t	key_len;
	char	*value;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		exit(1);
	key_len = ft_strchr(envp, '=') - envp;
	new->key = ft_strndup(envp, key_len);
	if (!is_name(new->key))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(envp, STDERR_FILENO);
		ft_putendl_fd("': not a valid identififer", STDERR_FILENO);
		free(new->key);
		free(new);
		return (NULL);
	}
	value = ft_strchr(envp, '=') + 1;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

char	**make_env_strs(t_env *env)
{
	size_t	env_size;
	char	**str;
	size_t	size;
	char	*tmp;

	env_size = ft_list_size(env);
	str = malloc(sizeof(char *) * (env_size + 1));
	if (str == NULL)
		exit(1);
	size = 0;
	while (size < env_size && env != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		if (tmp == NULL)
			exit(1);
		str[size] = ft_strjoin(tmp, env->value);
		if (str[size] == NULL)
			exit(1);
		free(tmp);
		size++;
		env = env->next;
	}
	str[size] = NULL;
	return (str);
}

size_t	ft_list_size(t_env *env)
{
	size_t	count;

	count = 0;
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}

// void	envs_str_free(t_env *env, char **str);

// int main(int ac, char **av, char **envp)
// {
// 	t_env *env;
// 	char **res;
// 	int i = 0;

// 	env = new_envs(envp);
// 	// while(env->next != NULL)
// 	// {
// 	// 	printf("%s\nkey: %s\nvalue: %s\n\n", envp[i], env->key, env->value);
// 	// 	env = env->next;
// 	// 	i++;
// 	// }
// 	// printf("%s\nkey: %s\nvalue: %s\n\n", envp[i], env->key, env->value);
// 	i = 0;
// 	res = make_env_strs(env);
// 	while (res[i] != NULL)
// 	{
// 		printf("%s\n", res[i]);
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// 	// str_array_free(res);
// 	// envs_free(env);
// 	envs_str_free(env, res);

// }

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q a.out");
// }
