/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:28:49 by resaito           #+#    #+#             */
/*   Updated: 2023/12/01 15:24:10 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	envs_free(t_env *env)
{
	if (env->next)
		envs_free(env->next);
	free(env->key);
	free(env->value);
	free(env);
}

void	envs_str_free(t_env *env, char **str)
{
	envs_free(env);
	str_array_free(str);
}
