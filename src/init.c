/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:15:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/31 01:44:59 by fwatanab         ###   ########.fr       */
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
