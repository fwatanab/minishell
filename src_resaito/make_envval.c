/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:04 by resaito           #+#    #+#             */
/*   Updated: 2023/12/04 14:20:06 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_envval	*make_envval(t_env *env)
{
	t_envval	*envval;

	envval = malloc(sizeof(t_envval) * 1);
	if (envval == NULL)
		exit(1);
	envval->env = env;
	envval->status = 0;
	return (envval);
}
