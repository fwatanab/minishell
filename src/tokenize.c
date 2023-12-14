/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:13:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/13 18:47:06 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_token(t_token_list **list, char *token)
{
	t_token_list	*new_node;
	t_token_list	**current;

	new_node = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_node)
	{
		list_free(list);
		malloc_error();
	}
	new_node->token = ft_strdup(token);
	if (!new_node->token)
	{
		free(new_node);
		list_free(list);
		malloc_error();
	}
	new_node->next = NULL;
	current = list;
	while (*current)
		current = &(*current)->next;
	*current = new_node;
}

static t_token_list	*create_list(const char *str, \
		t_token_list *list, t_token_check *check)
{
	if (str > check->start)
	{
		check->token = strndup(check->start, str - check->start);
		if (!check->token)
		{
			list_free(&list);
			malloc_error();
		}
		add_token(&list, check->token);
		free(check->token);
	}
	return (list);
}

static const char	*check_cmd_type(const char *str)
{
	bool	in_quote;

	in_quote = false;
	while (*str)
	{
		if (!in_quote && (*str == D_QUOTE || *str == S_QUOTE))
			in_quote = true;
		else if (in_quote && (*str == D_QUOTE || *str == S_QUOTE))
			in_quote = false;
		else if (!in_quote && (*str == SPACE || *str == PYPE
				|| *str == REDIR_IN || *str == REDIR_OUT))
			break ;
		str++;
	}
	return (str);
}

t_token_list	*tokenize(const char *str)
{
	t_token_list	*list;
	t_token_check	*check;

	list = NULL;
	check = checker_init();
	while (*str)
	{
		while (*str == SPACE)
			str++;
		check->start = str;
		str = check_cmd_type(str);
		if (*check->start == PYPE || *check->start == REDIR_IN
			|| *check->start == REDIR_OUT)
		{
			check->start = str;
			str++;
			list = create_list(str, list, check);
		}
		else
			list = create_list(str, list, check);
	}
	free(check);
	return (list);
}
