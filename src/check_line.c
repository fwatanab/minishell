/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:15:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/12 23:27:48 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	type_count(const char *str, t_envval *envval)
{
	int	redir;
	int	pype;

	redir = 0;
	pype = 0;
	while (*str)
	{
		if (*str == '<' || *str == '>')
			redir++;
		else if (*str == '|')
			pype++;
		str++;
	}
	if (redir || pype)
	{
		printf("minishell: syntax error near unexpected token\n");
		envval->status = 258;
	}
}

int	is_only_space(const char *str, t_envval *envval)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == ' ' || *tmp == '\t' || *tmp == '\n'
			|| *tmp == '\v' || *tmp == '\f' || *tmp == '\r'
			|| *tmp == '<' || *tmp == '>' || *tmp == '|')
			;
		else
			return (1);
		tmp++;
	}
	type_count(str, envval);
	return (0);
}

void	malloc_error(void)
{
	printf("%s\n", "Failed to allocate memory");
	exit(EXIT_FAILURE);
}
