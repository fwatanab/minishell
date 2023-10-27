/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:21:46 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/20 21:30:08 by fwatanab         ###   ########.fr       */
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

void	printer(t_node *node, char c)
{
	if (!node)
		return ;
	if (c == 'l')
	{
		printf("left %s\n", node->value);
		printf("left %u\n\n", node->type);
		printf("right %s\n", node->right->value);
		printf("right %u\n\n", node->right->type);
		printer(node->left, 'l');
	}
}

//void	print_node(t_node *node)
//{
//	if (!node)
//		return ;
//	while (node->right)
//	{
//		printf("node_value-> %s\n", node->value);
//		printf("node_type-> %u\n\n", node->type);
//		printf("node_left->value %s\n", node->left->value);
//		printf("node_left->type %u\n\n", node->left->type);
//		if (node->left->left)
//			printer(node->left, 'l');
//		if (node->left->right)
//		{
//			printer(node->right, 'r');
////			printf("node_left->right->value %s\n", node->left->right->value);
////			printf("node_left->right->type %u\n\n", node->left->right->type);
//		}
//		printf("node_right->value %s\n", node->right->value);
//		printf("node_right->type %u\n\n", node->right->type);
//		printf("-------node_right-------\n\n");
//		node = node->right;
//	}
//}

void	print_node(t_node *node)
{
	if (!node)
		return ;
	printf("node_value-> %s\n", node->value);
	printf("node_type-> %u\n\n", node->type);
	printf("--------------\n\n");
	printf("left\n");
	print_node(node->left);
	printf("right\n");
	print_node(node->right);
}
