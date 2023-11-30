/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:12:57 by resaito           #+#    #+#             */
/*   Updated: 2023/11/30 15:17:10 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*env_init(char **envp)
{
	t_env	*env;
	pid_t	pid;

	env = malloc(sizeof(t_env) * 1);
	if (env == NULL)
		exit(1);
	env->env = envp;
	env->pid = pid;
	return (env);
}
