/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:02:12 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/03 17:39:05 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pop_token(t_token_list **list)
{
	char	*value;

	if (!(*list))
		return (NULL);
	value = (*list)->token;
	*list = (*list)->next;
	return (value);
}

static void	copy_elements(char **new_array, char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			str_array_free(new_array);
			malloc_error();
		}
		i++;
	}
}

char	**add_array(char **array, char *token)
{
	char	**new_array;
	size_t	len;

	len = 0;
	if (array && array[len])
	{
		while (array[len])
			len++;
	}
	new_array = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_array)
	{
		str_array_free(array);
		malloc_error();
	}
	copy_elements(new_array, array, len);
	new_array[len] = ft_strdup(token);
	if (!new_array[len])
	{
		str_array_free(new_array);
		malloc_error();
	}
	new_array[len + 1] = NULL;
	str_array_free(array);
	return (new_array);
}
