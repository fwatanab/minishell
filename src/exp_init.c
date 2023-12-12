/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:07:38 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:07:39 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

t_parm	*parameter_init(char *token)
{
	t_parm	*new;

	new = (t_parm *)malloc(sizeof(t_parm));
	if (!new)
		return (NULL);
	new->tmp = token;
	new->str = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->str[0] = '\0';
	new->env_var = NULL;
	new->len = 0;
	return (new);
}
