/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:48:34 by fwatanab          #+#    #+#             */
/*   Updated: 2024/01/06 16:06:20 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*create_redir(void)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = NULL;
	new->next = NULL;
	return (new);
}

static void	set_redir_type(t_redir *redir, char *token)
{
	if (ft_strcmp(token, "<") == 0)
		redir->type = N_REDIR_IN;
	else if (ft_strcmp(token, ">") == 0)
		redir->type = N_REDIR_OUT;
	else if (ft_strcmp(token, "<<") == 0)
		redir->type = N_REDIR_HERE;
	else if (ft_strcmp(token, ">>") == 0)
		redir->type = N_REDIR_APPEND;
}

static void	add_redir_file(t_redir *redir, char *token)
{
	if (!token && (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
			|| ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">>") == 0))
		return ;
	redir->file = ft_strdup(token);
	if (!redir->file)
		return ;
}

static int	check_redir_error(t_redir *redir, t_token_list **list)
{
	if (!redir)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (!*list)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		redir->type = 0;
	}
	return (0);
}

t_redir	*redir_parse(t_redir *redir, \
		t_token_list **list, char *token)
{
	t_redir	*current;

	if (!list || (ft_strcmp(token, "<") != 0 && ft_strcmp(token, ">") != 0
			&& ft_strcmp(token, "<<") != 0 && ft_strcmp(token, ">>") != 0))
		return (NULL);
	if (!redir)
	{
		redir = create_redir();
		current = redir;
	}
	else
	{
		current = redir;
		while (current->next)
			current = current->next;
		current->next = create_redir();
		current = current->next;
	}
	set_redir_type(current, token);
	if (check_redir_error(redir, list) == 1)
		return (NULL);
	if (*list)
		token = pop_token(list);
	add_redir_file(current, token);
	return (redir);
}
