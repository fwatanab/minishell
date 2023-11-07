/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:15:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/07 20:16:21 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token_check	*checker_init(void)
{
	t_token_check	*check;

	check = (t_token_check *)malloc(sizeof(t_token_check));
	if (!check)
		malloc_error();
	check->start = NULL;
	check->token = NULL;
	check->d_quote = false;
	check->s_quote = false;
	return (check);
}

t_node	*node_init(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->args = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	all_node_init(t_node *node)
{
	node->left = node_init();
	if (!node->left)
	{
		free(node);
		return ;
	}
	node->right = node_init();
	if (!node->right)
	{
		free(node);
		free(node->left);
		return ;
	}
	node->name = NULL;
	node->args = NULL;
}

t_redir	*create_redir(size_t len)
{
	t_redir		*new;
	size_t		i;

	if (!len)
		return (NULL);
	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (i <= len)
		new->file[i++] = NULL;
	new->next = NULL;
	return (new);
}
Help people interested in this repository understand your project by adding a README.