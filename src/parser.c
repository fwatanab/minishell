/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:38:33 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/03 17:38:38 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	updata_type_value(t_node *node, \
		t_token_list **list, t_parse_check *key)
{
	t_token_list	*tmp;

	if (!key->key_type)
	{
		key->key_type = true;
		node->type = N_PIPE;
		node->name = ft_strdup(key->token);
		if (!node->name)
		{
			node_free(node);
			malloc_error();
		}
		key->key_list = *list;
	}
	else
	{
		tmp = key->key_list;
		if (node->right->args)
			str_array_free(node->right->args);
		if (node->right->name)
			free(node->right->name);
		node->right = parser(node->right, &tmp, key);
		return (1);
	}
	return (0);
}

static t_node	*updata_name_value(t_node *node, \
		t_parse_check *key, t_token_list **list)
{
	if (key->key_type)
	{
		if (!node->right->name)
			node->right->name = search_path(key->token);
		node->right->type = N_COMMAND;
		node->right->args = add_array(node->right->args, key->token);
	}
	else if (!key->key_type)
	{
//		if (ft_strcmp(key->token, "<") == 0)
//		{
//			key->key_redir = true;
//			node->left = redir_parse(node->left, list, key);
//		}
		if (!node->left->name)
			node->left->name = search_path(key->token);
		node->left->type = N_COMMAND;
		node->left->args = add_array(node->left->args, key->token);
	}
	return (node);
}

t_node	*parser(t_node *node, t_token_list **list, t_parse_check *key)
{
	all_node_init(node);
	if (!node)
		return (NULL);
	key->key_type = false;
	while (*list)
	{
		key->token = pop_token(list);
		if (!key->token)
			return (NULL);
		if (ft_strcmp(key->token, "|") == 0)
		{
			if (updata_type_value(node, list, key) == 1)
				break ;
		}
		else
			node = updata_name_value(node, key, list);
	}
	if (!node && node->left && !node->right)
	{
		node->args = node->left->args;
		node->name = node->left->name;
		node->left->args = NULL;
		node->left->name = NULL;
	}
	return (node);
}

t_node	*parser_start(t_token_list **list)
{
	t_node			*node;
	t_parse_check	*key;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	key = (t_parse_check *)malloc(sizeof(t_parse_check));
	if (!key)
		return (NULL);
	node = parser(node, list, key);
	free(key);
	return (node);
}
