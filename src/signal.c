/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/08 16:44:30 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t received_signal = 0;

void	signal_handler(int sig)
{
	received_signal = sig;
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
	received_signal = sig;
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: ", 6);
		ft_putnbr_fd(sig, 1);
		write(1, "\n", 1);
	}
}

void	check_status(sig_atomic_t received_signal, \
		t_envval *envval, int fork)
{
	if (!fork)
	{
		if (received_signal)
		{
			if (received_signal == SIGINT)
				envval->status = 1;
			received_signal = 0;
		}
	}
	else if (fork)
	{
		if (received_signal)
		{
			if (received_signal == SIGINT)
				envval->status = 130;
			else if (received_signal == SIGQUIT)
				envval->status = 131;
			received_signal = 0;
		}
	}
}
