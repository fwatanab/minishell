/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:08:23 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/28 16:09:04 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*create_home(char *pwd)
{
	char	*home;
	size_t	i;
	size_t	flag;

	home = pwd;
	i = 0;
	flag = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			flag++;
		if (flag == 3)
			break ;
		home[i] = pwd[i];
		i++;
	}
	home[i] = '\0';
	return (home);
}

static bool	find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

void	add_minimal_env_if_missing(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	if (!find_env_var(*env, "PATH"))
		envadd_back(env, new_env("PATH=/usr/local/bin:/usr/bin:/bin"));
	if (!find_env_var(*env, "PWD"))
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			tmp = ft_strjoin("PWD=", cwd);
			envadd_back(env, new_env(tmp));
			free(tmp);
		}
	}
	if (!find_env_var(*env, "HOME"))
	{
		tmp = create_home(cwd);
		tmp = ft_strjoin("HOME=", tmp);
		envadd_back(env, new_env(tmp));
		free(tmp);
	}
	if (!find_env_var(*env, "SHELL"))
		envadd_back(env, new_env("SHELL=/bin/zsh"));
}
