/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:47:48 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/13 18:52:39 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

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

char	*check_command(char *str, t_envval *envval)
{
	char	*result;
	char	*token;

	result = check_close_quote(str);
	token = check_env_var_braces(str);
	if (result || token)
	{
		str[0] = '\0';
		envval->status = 1;
		if (result)
			printf("Unbalanced quote found: %s\n", result);
		else if (token)
			printf("Unbalanced quote found: %s\n", token);
		return (str);
	}
	return (str);
}
