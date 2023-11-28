/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:26:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/27 17:24:45 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_c_handler(int sig_num)
{
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
	printf(MINISHELL);
}

//void	signal_c_handler(int sig_num)
//{
//	printf("test\n");
//	exit(0);
//}
