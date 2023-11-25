/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/25 16:34:59 by fwatanab         ###   ########.fr       */
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
	if (!parm->str)
		return (token);
	new_token = ft_strdup(parm->str);
	free(parm->str);
	free(parm);
	free(token);
	return (new_token);
}

char	*delete_quote(char	*token)
{
	char	*new_token;
	size_t	i;
	size_t	j;

	if (!token || (token[0] != '\'' && token[0] != '"'))
		return (token);
	new_token = (char *)malloc(sizeof(char) * (ft_strlen(token) - 1));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 1;
	while (token[j])
	{
		if (token[j] == '\'' || token[j] == '"')
			break ;
		new_token[i++] = token[j++];
	}
	new_token[i] = '\0';
	free(token);
	return (new_token);
}

char	*check_command(char *str)
{
	char	*tmp;
	bool	quote;
	size_t	open;
	size_t	close;

	tmp = str;
	quote = false;
	open = 0;
	close = 0;
	while (*tmp)
	{
		if (!quote && (*tmp == '\'' || *tmp == '"'))
			quote = true;
		else if (quote && (*tmp == '\'' || *tmp == '"'))
			quote = false;
		else if (*tmp == '$' && *(tmp + 1) == '{')
			open++;
		else if ((close + 1) == open && *tmp == '}')
			close++;
		tmp++;
	}
	if (quote || (str[0] == '\'' && str[ft_strlen(str) - 1] == '"')
		|| (str[0] == '"' && str[ft_strlen(str)-1] == '\'') || open != close)
		str[0] = '\0';
	return (str);
}

void	expansion(char **array)
{
	char	*new_array;
	size_t	i;

	i = 0;
	new_array = NULL;
	while (array[i])
	{
		array[i] = check_command(array[i]);
		array[i] = expand_parameter(array[i]);
		array[i] = delete_quote(array[i]);
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
