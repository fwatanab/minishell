/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:28:49 by resaito           #+#    #+#             */
/*   Updated: 2023/12/08 13:38:38 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	envs_free(t_env *env)
{
	if (!env)
		return ;
	if (env->next)
		envs_free(env->next);
	env_free(env);
}

void	envs_str_free(t_env *env, char **str)
{
	envs_free(env);
	str_array_free(str);
}

void	env_free(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	if (env)
		free(env);
}
