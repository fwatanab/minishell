/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:15:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/27 19:31:35 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
