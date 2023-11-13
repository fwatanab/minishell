/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:23:51 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/08 19:06:45 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	list_free(t_token_list **list)
{
	t_token_list	*tmp;
	t_token_list	*next;

	if (!list && !*list)
		return ;
	tmp = *list;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = next;
	}
	*list = NULL;
}

void	str_array_free(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	redir_free(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	while (redir)
	{
		tmp = redir;
		if (redir->file)
			str_array_free(tmp->file);
		redir = redir->next;
		free(tmp);
	}
}

void	node_free(t_node *node)
{
	if (!node)
		return ;
	if (node->args)
		str_array_free(node->args);
	if (node->name)
		free(node->name);
	if (node->redir)
		redir_free(node->redir);
	if (node->left)
		node_free(node->left);
	if (node->right)
		node_free(node->right);
	free(node);
}

void	malloc_error(void)
{
	printf("%s\n", "Failed to allocate memory");
	exit(EXIT_FAILURE);
}
