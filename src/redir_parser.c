/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:48:34 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/08 19:55:43 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	redir_size(t_token_list **list, char *token)
{
	size_t			len;
	t_token_list	*tmp;

	tmp = *list;
	len = 0;
	if (tmp && (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0))
		token = pop_token(&tmp);
	while (ft_strcmp(token, "|") != 0
		&& ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0)
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

t_redir	*redir_parse(t_redir *redir, t_token_list **list, char *token)
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
