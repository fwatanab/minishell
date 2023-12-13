/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/13 19:16:23 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

char	*expand_parameter(char *token, t_envval *envval)
{
	t_parm	*parm;
	char	*new_token;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init(token);
	if (!parm)
		return (token);
	parm->str = check_parameter(parm, envval);
	if (!parm->str)
		return (token);
	new_token = ft_strdup(parm->str);
	free(parm->str);
	free(parm);
	free(token);
	return (new_token);
}

static char	*delete_quote(char *token)
{
	size_t	length;
	char	*result;
	size_t	i;
	size_t	j;

	if (token == NULL)
		return (NULL);
	length = strlen(token);
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < length)
	{
		if (token[i] != '\'' && token[i] != '\"')
			result[j++] = token[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*expansion(char **array, t_envval *envval)
{
	char	*new_array;
	size_t	i;

	i = 0;
	new_array = NULL;
	while (array[i])
	{
		array[i] = check_command(array[i], envval);
		array[i] = expand_parameter(array[i], envval);
		array[i] = delete_quote(array[i]);
		i++;
	}
	if (array[0])
		return (search_path(array[0], envval->env));
	return (NULL);
}

void	check_exp(t_node *node, t_envval *envval)
{
	size_t	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
		node->name = expansion(node->args, envval);
	if (node->left)
		check_exp(node->left, envval);
	if (node->right)
		check_exp(node->right, envval);
}
