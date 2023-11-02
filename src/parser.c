/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/02 17:14:42 by fwatanab         ###   ########.fr       */
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
	char	**new_array;
	size_t	len;
	size_t	i;

	len = 0;
	if (array && array[len])
	{
		while (array[len])
			len++;
	}
	new_array = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_array)
	{
		str_array_free(array);
		malloc_error();
	}
	i = 0;
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			str_array_free(new_array);
			malloc_error();
		}
		i++;
	}
	new_array[len] = ft_strdup(token);
	if (!new_array[len])
	{
		str_array_free(new_array);
		malloc_error();
	}
	new_array[len + 1] = NULL;
	str_array_free(array);
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
//			str_array_free(node->args);
			node->args = NULL;
		}
		node->name = key->token;
		key->key_list = *list;
	printf("11     %s\n", (*list)->token);
	}
	else
	{
		printf("--------     %s\n", (*list)->token);
		node->right = parser(node->right, &key->key_list, key);
		return (1);
	}
	return (0);
}

static t_node	*updata_name_value(t_node *node, \
		t_parse_check *key, t_token_list **list)
{
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
	printf("     %s\n", (*list)->token);
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
	if (node->type == N_COMMAND && !node->right)
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
