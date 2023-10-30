/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:23:51 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/31 02:24:08 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	list_free(t_token_list **list)
{
	t_token_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
}

void	str_array_free(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	node_free(t_node *node)
{
	if (!node)
		return ;
	node_free(node->left);
	node_free(node->right);
	str_array_free(node->args);
	free(node->name);
	free(node);
}

void	malloc_error(void)
{
	printf("%s\n", "Failed to allocate memory");
	exit(EXIT_FAILURE);
}
