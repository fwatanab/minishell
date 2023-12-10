/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:46:50 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/07 19:10:16 by fwatanab         ###   ########.fr       */
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

void	execute_exit(char **cmd, t_envval *envval)
{
	int		status;
	size_t	len;

	status = 0;
	len = 0;
	while (cmd[len])
		len++;
	if (len <= 2 && ft_strcmp(cmd[0], "exit") == 0)
	{
		if (cmd[1] != NULL && is_numeric_str(cmd[1]))
			status = ft_atoi(cmd[1]);
		else if (cmd[1] != NULL)
		{
			write(2, "exit: numeric argument required\n", 33);
			status = 255;
		}
		else
			status = envval->status;
		write(1, "exit\n", 5);
		exit(status);
	}
}
