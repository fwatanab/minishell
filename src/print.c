/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:21:46 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/30 17:25:07 by fwatanab         ###   ########.fr       */
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


void print_indent(int depth)
{
	for (int i = 0; i < depth; ++i) {
		printf("  ");
	}
}

void print_tree(t_node *node, int depth)
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

void	print_node(t_node *node)
{
	size_t	i;

	if (!node)
		return ;
	printf("name %s\n", node->name);
	i = 0;
	while (node->args[i])
	{
		printf("%s ", node->args[i]);
		i++;
	}
	printf("\n");
	printf("node_type-> %u\n\n", node->type);
	printf("--------------\n\n");
	printf("left\n");
	print_node(node->left);
	printf("right\n");
	print_node(node->right);
}
