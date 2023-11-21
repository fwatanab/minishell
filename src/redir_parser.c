/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:48:34 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/21 18:25:47 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	redir_size(t_token_list **list, char *token)
{
	size_t			len;
	t_token_list	*tmp;

	tmp = *list;
	len = 0;
	if (tmp && (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
			|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0))
		token = pop_token(&tmp);
	while (ft_strcmp(token, "|") != 0
		&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
		&& ft_strcmp(token, "<<") != 0 && ft_strcmp(token, ">>") != 0)
	{
		len++;
		if (!tmp)
			break ;
		token = pop_token(&tmp);
	}
	return (len);
}

static t_redir	*create_redir(size_t len)
{
	t_redir		*new;
	size_t		i;

	if (!len)
		return (NULL);
	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new->file)
	{
		free(new);
		return (NULL);
	}
	i = 0;
	while (i <= len)
		new->file[i++] = NULL;
	new->next = NULL;
	return (new);
}

static char	*add_redir_file(t_node *node, t_redir *redir, t_token_list **list)
{
	char	*token;
	size_t	i;

	if (*list)
		token = pop_token(list);
	i = 0;
	while (ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
		&& ft_strcmp(token, "<<") != 0 && ft_strcmp(token, ">>") != 0)
	{
		redir->file[i] = ft_strdup(token);
		if (!redir->file[i])
		{
			list_free(list);
			node_free(node);
			malloc_error();
		}
		if (!*list || ft_strcmp((*list)->token, "|") == 0)
			break ;
		token = pop_token(list);
		i++;
	}
	return (token);
}

t_redir	*redir_parse(t_node *node, t_redir *redir, \
		t_token_list **list, char *token)
{
	if (!list || (ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
			&& ft_strcmp(token, "<<") != 0 && ft_strcmp(token, ">>") != 0))
		return (NULL);
	redir = create_redir(redir_size(list, token));
	if (!redir)
	{
		list_free(list);
		node_free(node);
		malloc_error();
	}
	if (ft_strcmp(token, "<") == 0)
		redir->type = N_REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		redir->type = N_REDIR_OUT;
	else if (ft_strcmp(token, "<<") == 0)
		redir->type = N_REDIR_HERE;
	else if (ft_strcmp(token, ">>") == 0)
		redir->type = N_REDIR_APPEND;
	token = add_redir_file(node, redir, list);
	if (*list && (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
			|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0))
		redir->next = redir_parse(node, redir->next, list, token);
	return (redir);
}
