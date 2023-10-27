/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/25 18:52:33 by fwatanab         ###   ########.fr       */
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

static int	updata_type_value(t_node *node, \
		t_token_list **list, t_parse_check *key)
{
	if (!key->key_type)
	{
		key->key_type = true;
		node->type = N_PYPE;
		node->value = key->token;
		key->key_list = *list;
	}
	else
	{
		node->right = parser(node->right, &key->key_list, key);
		return (1);
	}
	return (0);
}

//static t_node	*redir_parse(t_node *node, t_token_list **list, t_parse_check *key)
//{
//
//	all_node_init(node);
//	node->left->value = node->value;
//	node->value = key->token;
//	node->type = N_REDIR_IN;
//	while (*list)
//	{
//		key->token = ft_strdup(pop_token(list));
//		if (ft_strcmp(key->token, "|") == 0)
//			break ;
//		if (ft_strcmp(key->token, "<") == 0)
//		{
//			node->left = redir_parse(node->left, list, key);
//			break ;
//		}
//		else
//		{
//			node->right->value = my_strjoin(node->right->value, key->token);
//			node->right->value = my_strjoin(node->right->value, " ");
//		}
//	}
//	return (node);
//}

static t_node	*updata_name_value(t_node *node, t_parse_check *key, t_token_list **list)
{
	if (key->key_type)
	{
		node->right->type = N_COMMAND;
		node->right->value = my_strjoin(node->right->value, key->token);
		node->right->value = my_strjoin(node->right->value, " ");
	}
	else if (!key->key_type)
	{
//		if (ft_strcmp(key->token, "<") == 0)
//		{
//			key->key_redir = true;
//			node->left = redir_parse(node->left, list, key);
//		}
//		else
//		{
			node->left->type = N_COMMAND;
			node->left->value = my_strjoin(node->left->value, key->token);
			node->left->value = my_strjoin(node->left->value, " ");
//		}
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
	if (!node->value)
	{
		node->value = node->left->value;
		node->left->value = NULL;
	}
	return (node);
}

void print_tree(t_node *node, int depth) {
    if (!node) return;

    // 右の子を表示
    if (node->right) {
        print_tree(node->right, depth + 1);
    }

    // 現在のノードの深さに応じてスペースを追加
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    // 現在のノードの値を表示
    printf("%s\n", node->value);

    // 左の子を表示
    if (node->left) {
        print_tree(node->left, depth + 1);
    }
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
    print_tree(node, 0);  // rootは木のルートノード
//	print_node(node);
	free(key);
	return (node);
}
