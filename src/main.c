/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:52 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/29 20:34:50 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell(char *line)
{
	t_token_list	*list;
	t_token_list	*tmp;
	t_node			*node;

	list = tokenize(line);
	tmp = list;
	check_token(list);
//	print_list(list);
	node = parser_start(&list);
	check_exp(node);
	ft_execution(node);
//	print_node(node);
	list_free(&tmp);
	node_free(node);
}

void	bash_loop(void)
{
	char	*line;

	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		line = readline(MINISHELL);
		if (!line)
			break ;
		else if (line[1] == '\0')
			free(line);
		else
		{
			add_history(line);
			minishell(line);
			free(line);
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		bash_loop();
	return (0);
}
