/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/21 18:22:12 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	updata_type_value(t_node *node, \
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
		check_right_node(node);
		node->right = parser(node->right, &tmp, key);
		return (false);
	}
	return (true);
}

static void	updata_name_value(t_node *node, \
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
		if (!node->left->name)
			node->left->name = search_path(key->token);
		node->left->type = N_COMMAND;
		node->left->args = add_array(node->left->args, key->token);
	}
}

static bool	redir_checker(t_node *node, t_parse_check *key, t_token_list **list)
{
	if (ft_strcmp(key->token, "<") == 0 || ft_strcmp(key->token, ">") == 0
		|| ft_strcmp(key->token, "<<") == 0 || ft_strcmp(key->token, ">>") == 0)
	{
		if (key->key_type)
			node->right->redir = redir_parse(\
					node, node->right->redir, list, key->token);
		else if (!key->key_type)
			node->left->redir = redir_parse(\
					node, node->left->redir, list, key->token);
		return (true);
	}
	return (false);
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
			if (updata_type_value(node, list, key) == false)
				break ;
		}
		else
		{
			if (redir_checker(node, key, list) == false)
				updata_name_value(node, key, list);
		}
	}
	if (node->type == NONE)
		one_n_command(node);
	return (node);
}

t_node	*parser_start(t_token_list **list)
{
	t_node			*node;
	t_parse_check	*key;

	node = (t_node *)ft_calloc(sizeof(t_node), 1);
	if (!node)
		return (NULL);
	key = (t_parse_check *)ft_calloc(sizeof(t_parse_check), 1);
	if (!key)
		return (NULL);
	node = parser(node, list, key);
	free(key);
	return (node);
}
