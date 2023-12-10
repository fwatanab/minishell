/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/10 18:51:51 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	sig_status = 0;

void	signal_handler(int sig)
{
	sig_status = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		;
}

void	signal_fork_handler(int sig)
{
	sig_status = sig;
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: ", 6);
		ft_putnbr_fd(sig, 1);
		write(1, "\n", 1);
	}
}

void	check_status(t_envval *envval, int fork)
{
	if (!fork)
	{
		if (sig_status)
		{
			if (sig_status == SIGINT)
				envval->status = 1;
			sig_status = 0;
		}
	}
	else if (fork)
	{
		if (sig_status)
		{
			if (sig_status == SIGINT)
				envval->status = 130;
			else if (sig_status == SIGQUIT)
				envval->status = 131;
			sig_status = 0;
		}
	}
}
