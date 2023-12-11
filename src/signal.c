/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 09:52:38 by fwatanab         ###   ########.fr       */
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
		env_status = 1;
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
	env_status = 128 + sig;
}

//void	check_status(t_envval *envval, int fork)
//{
//	if (!fork)
//	{
//		if (sig_status)
//		{
//			if (sig_status == SIGINT)
//				envval->status = 1;
//			sig_status = 0;
//		}
//	}
//	else if (fork)
//	{
//		if (sig_status)
//		{
//			if (sig_status == SIGINT)
//			envval->status = 128 + sig_status;
//			else if (sig_status == SIGQUIT)
//				envval->status = 131;
//			sig_status = 0;
//		}
//	}
//}
