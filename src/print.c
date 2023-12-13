/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:21:46 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/12 21:03:25 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token_list *list)
{
	while (list)
	{
		printf("list-> %s\n", list->token);
		list = list->next;
	}
	printf("------------------\n\n");
}

static void	print_redir(t_redir *redir)
{
	if (!redir)
		return ;
	printf("r_type: %u\n", redir->type);
	printf("file:\n");
	printf("     %s\n", redir->file);
	print_redir(redir->next);
}

static void	printer(t_node *node)
{
	size_t	i;

	if (node->name)
		printf("name: %s\n", node->name);
	printf("type: %u\n", node->type);
	if (node->args)
	{
		i = 0;
		printf("args:\n");
		while (node->args[i])
		{
			printf("     [%zu] %s\n", i, node->args[i]);
			i++;
		}
	}
}

void	print_node(t_node *node)
{
	if (!node)
		return ;
	printer(node);
	if (node->redir)
	{
		printf("redir:\n");
		print_redir(node->redir);
	}
	printf("--------------\n");
	if (node->left)
	{
		printf("left\n");
		print_node(node->left);
	}
	if (node->right)
	{
		printf("right\n");
		print_node(node->right);
	}
}
