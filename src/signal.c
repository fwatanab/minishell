/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/15 17:51:49 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_status = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig_status = 1;
	}
	else if (sig == SIGQUIT)
		;
}

void	signal_fork_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: ", 6);
		ft_putnbr_fd(sig, 1);
		write(1, "\n", 1);
	}
	if (sig)
		g_sig_status = 128 + sig;
}

void	signal_heredoc_handler(int sig)
{
	if (sig == SIGINT)
		g_sig_status = 1;
	else if (sig == SIGQUIT)
		;
}

void	check_status(t_envval *envval)
{
	if (g_sig_status)
	{
		envval->status = g_sig_status;
		g_sig_status = 0;
	}
}

int	signal_check(void)
{
	if (g_sig_status)
		rl_done = 1;
	return (0);

}
