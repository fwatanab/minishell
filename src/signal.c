/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/29 20:31:41 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler(int sig)
{
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
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: ", 6);
		ft_putnbr_fd(sig, 1);
		write(1, "\n", 1);
	}
}
