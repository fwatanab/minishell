/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:07:38 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/14 16:32:40 by fwatanab         ###   ########.fr       */
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

t_quote_status	*quote_status_init(char *token)
{
	t_quote_status	*q_status;

	if (!token)
		return (NULL);
	q_status = (t_quote_status *)malloc(sizeof(t_quote_status));
	if (!q_status)
		return (NULL);
	q_status->len = ft_strlen(token);
	q_status->result = ft_calloc(q_status->len + 1, sizeof(char));
	if (!q_status->result)
	{
		free(q_status);
		return (NULL);
	}
	q_status->s_quote = false;
	q_status->d_quote = false;
	q_status->i = 0;
	return (q_status);
}
