/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:25:36 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/27 18:53:01 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_token(t_token_list *list)
{
	t_token_list	*tmp;
	t_token_list	*new;
	char			*old_token;

	tmp = list;
	while (tmp->next)
	{
		if ((ft_strcmp(tmp->token, "<") == 0
				&& ft_strcmp(tmp->next->token, "<") == 0)
			|| (ft_strcmp(tmp->token, ">") == 0
				&& ft_strcmp(tmp->next->token, ">") == 0))
		{
			old_token = tmp->token;
			tmp->token = ft_strjoin(tmp->token, tmp->next->token);
			free(old_token);
			new = tmp->next->next;
			free(tmp->next->token);
			free(tmp->next);
			tmp->next = new;
		}
		tmp = tmp->next;
	}
}
