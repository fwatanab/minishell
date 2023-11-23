/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/23 18:54:43 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expansion.h"

char	*expand_parameter(char *token)
{
	t_parm	*parm;
	char	*new_token;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init(token);
	if (!parm)
		return (token);
	parm->str = check_parameter(parm, token);
	new_token = ft_strdup(parm->str);
	free(parm->str);
	free(parm);
	free(token);
	return (new_token);
}

void	expansion(char **array)
{
	char	*new_array;
	size_t	i;

	i = 0;
	new_array = NULL;
	while (array[i])
	{
		array[i] = expand_parameter(array[i]);
		i++;
	}
}

void	check_exp(t_node *node)
{
	size_t	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
		expansion(node->args);
	if (node->left)
		check_exp(node->left);
	if (node->right)
		check_exp(node->right);
}
