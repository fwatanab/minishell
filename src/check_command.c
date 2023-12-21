/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:47:48 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/22 06:11:44 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

int	check_redir(t_node *node, t_envval *envval)
{
	if (node->redir)
	{
		if (node->redir->type == 0)
		{
			envval->status = 258;
			return (1);
		}
		node->redir->file = check_command(node->redir->file, node, envval);
		node->redir->file = delete_quote(node->redir->file);
	}
	return (0);
}

static char	*check_close_quote(char *str)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	while (*str != '\0')
	{
		if (*str == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*str == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		str++;
	}
	if (in_single_quote)
		return ("\'");
	else if (in_double_quote)
		return ("\"");
	else
		return (NULL);
}

static char	*check_env_var_braces(char *str)
{
	char	*tmp;
	size_t	open;
	size_t	close;

	tmp = str;
	open = 0;
	close = 0;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) == '{')
			open++;
		else if ((close + 1) == open && *tmp == '}')
			close++;
		tmp++;
	}
	if (open != close)
	{
		str[0] = '\0';
		return ("}");
	}
	return (NULL);
}

static void	delete_node(t_node *node, t_envval *envval)
{
	size_t	i;

	if (!node)
		return ;
	i = 0;
	if (node->args)
	{
		while (node->args[i])
		{
			node->args[i][0] = '\0';
			i++;
		}
	}
	if (node->redir)
		node->redir->file[0] = '\0';
	if (node->left)
		delete_node(node->left, envval);
	if (node->right)
		delete_node(node->right, envval);
}

char	*check_command(char *str, t_node *node, t_envval *envval)
{
	char	*result;
	char	*token;

	result = check_close_quote(str);
	token = check_env_var_braces(str);
	if (token || result)
	{
		if (result)
			printf("minishell: Unclosed quote found: %s\n", result);
		if (token)
			printf("minishell: Unclosed brace found: %s\n", token);
		delete_node(node, envval);
	}
	return (str);
}
