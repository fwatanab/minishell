/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:13:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/31 02:35:44 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token_list	*add_token(t_token_list **list, char *token)
{
	t_token_list	*new_node;
	t_token_list	*tmp;

	new_node = (t_token_list *)malloc(sizeof(t_token_list));
	if (!new_node)
	{
		list_free(list);
		malloc_error();
	}
	new_node->token = ft_strdup(token);
	new_node->next = NULL;
	if (!(*list))
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (new_node);
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

static const char	*check_cmd_type(const char *str, t_token_check *check)
{
	while (*str)
	{
		if (!check->s_quote && !check->d_quote && *str == D_QUOTE)
			check->d_quote = true;
		else if (!check->d_quote && !check->s_quote && *str == S_QUOTE)
			check->s_quote = true;
		else if ((check->d_quote && *str == D_QUOTE)
			|| (check->s_quote && *str == S_QUOTE))
		{
			if (*str == D_QUOTE)
				check->d_quote = false;
			if (*str == S_QUOTE)
				check->s_quote = false;
			str++;
			break ;
		}
		else if (!check->d_quote && !check->s_quote && *str == SPACE)
			break ;
		else if (!check->d_quote && !check->s_quote && (*str == PYPE
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
		str = check_cmd_type(str, check);
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
