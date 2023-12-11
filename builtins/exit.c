/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:46:50 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 17:22:53 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

static bool	is_numeric_str(char *str)
{
	if (!str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit((int)*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

void	ft_exit(t_node *node, t_envval *envval)
{
	int		status;
	size_t	len;

	status = 0;
	len = 0;
	while (node->args[len])
		len++;
	if (len <= 2 && ft_strcmp(node->args[0], "exit") == 0)
	{
		if (node->args[1] != NULL && is_numeric_str(node->args[1]))
			status = ft_atoi(node->args[1]);
		else if (node->args[1] != NULL)
		{
			write(2, "exit: numeric argument required\n", 33);
			status = 255;
		}
		else
			status = envval->status;
		write(1, "exit\n", 5);
		node_free(node);
		exit(status);
	}
}
