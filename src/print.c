/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:21:46 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/08 09:31:20 by fwatanab         ###   ########.fr       */
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


void	print_indent(int depth)
{
	for (int i = 0; i < depth; ++i) {
		printf("  ");
	}
}

void	print_tree(t_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	print_indent(depth);
	printf("Type: %d\n", node->type);
	if (node->name)
	{
		print_indent(depth);
		printf("Name: %s\n", node->name);
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			print_indent(depth);
			printf("Arg[%d]: %s\n", i, node->args[i]);
			i++;
		}
	}
	if (node->left)
	{
		print_indent(depth);
		printf("Left:\n");
		print_tree(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("Right:\n");
		print_tree(node->right, depth + 1);
	}
}

void	print_redir(t_redir *redir)
{
	size_t	i;

	if (!redir)
		return ;
	printf("r_type: %u\n", redir->type);
	printf("redir:\n");
	i = 0;
	while (redir->file[i])
	{
		printf("     [%zu] %s\n", i, redir->file[i]);
		i++;
	}
	print_redir(redir->next);
}

void	print_node(t_node *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->name)
		printf("name: %s\n", node->name);
	if (node->args)
	{
		i = 0;
		printf("args:\n");
		while (node->args[i])
		{
			printf("     [%zu] %s\n",i , node->args[i]);
			i++;
		}
	}
	printf("type: %u\n", node->type);
	if (node->redir)
		print_redir(node->redir);
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
