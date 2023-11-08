/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/08 19:09:28 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*redir_parse(t_redir *redir, t_token_list **list, char *token)
{
	size_t	len;

	if (!list || (ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0))
		return (NULL);
	len = redir_size(list, token);
	redir = create_redir(len);
	if (!redir)
	{
		/////free
		malloc_error();
	}
	if (ft_strcmp(token, "<") == 0)
		redir->type = N_REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		redir->type = N_REDIR_OUT;
	token = pop_token(list);
	len = 0;
	while (ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0)
	{
		redir->file[len] = ft_strdup(token);
		if (!redir->file[len])
		{
			//////////free
			malloc_error();
		}
		if (!*list || ft_strcmp((*list)->token, "|") == 0)
			return (redir);
		token = pop_token(list);
		len++;
	}
	if (*list && (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0))
		redir->next = redir_parse(redir->next, list, token);
	return (redir);
}

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
		if (node->right->redir)
		{
			redir_free(node->right->redir);
			node->right->redir = NULL;
		}
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
		if (ft_strcmp(key->token, "<") == 0 || ft_strcmp(key->token, ">") == 0)
			node->right->redir = redir_parse(node->right->redir, list, key->token);
		else
		{
			if (!node->right->name)
				node->right->name = search_path(key->token);
			node->right->type = N_COMMAND;
			node->right->args = add_array(node->right->args, key->token);
		}
	}
	else if (!key->key_type)
	{
		if (ft_strcmp(key->token, "<") == 0 || ft_strcmp(key->token, ">") == 0)
			node->left->redir = redir_parse(node->left->redir, list, key->token);
		else
		{
			if (!node->left->name)
				node->left->name = search_path(key->token);
			node->left->type = N_COMMAND;
			node->left->args = add_array(node->left->args, key->token);
		}
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
	if (!node && !node->right)
	{
		node->args = node->left->args;
		node->name = node->left->name;
		node->redir = node->left->redir;
		node->left->args = NULL;
		node->left->name = NULL;
		node->left->redir = NULL;
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
