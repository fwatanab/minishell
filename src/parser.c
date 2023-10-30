/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/30 18:02:23 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*pop_token(t_token_list **list)
{
	char	*value;

	if (!(*list))
		return (NULL);
	value = (*list)->token;
	*list = (*list)->next;
	return (value);
}

static char	**add_array(char **array, char *token)
{
	size_t	len;
	size_t	i;
	char	**new_array;

	len = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	new_array = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[len] = ft_strdup(token);
	new_array[len + 1] = NULL;
	if (!array)
		free(array);
	return (new_array);
}

static int	updata_type_value(t_node *node, \
		t_token_list **list, t_parse_check *key)
{
	if (!key->key_type)
	{
		key->key_type = true;
		node->type = N_PIPE;
		if (node->args)
		{
			free(node->args);
			node->args = NULL;
		}
		node->name = key->token;
		key->key_list = *list;
	}
	else
	{
		node->right = parser(node->right, &key->key_list, key);
		return (1);
	}
	return (0);
}

static t_node	*updata_name_value(t_node *node, t_parse_check *key, t_token_list **list)
{ static size_t	i;

	if (key->key_type)
	{
		if (node->right->name == NULL)
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
		if (node->left->name == NULL)
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
	key->key_redir = false;
	while (*list)
	{
		if (!key->key_redir)
			key->token = pop_token(list);
		if (key->key_redir)
			key->key_redir = false;
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
	if (node->type == N_COMMAND)
	{
		node->args = node->left->args;
		node->left->args = NULL;
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
	print_tree(node, 0);
//	print_node(node);
	free(key);
	return (node);
}
