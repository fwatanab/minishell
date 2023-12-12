/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:48:34 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/12 21:56:46 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*create_redir(void)
{
	t_redir		*new;
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

t_redir	*redir_parse(t_node *node, t_redir *redir, \
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
		redir->next = create_redir();
		current = redir->next;
	}
	if (!redir)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	set_redir_type(current, token);
	token = pop_token(list);
	add_redir_file(current, token);
	return (redir);
}
