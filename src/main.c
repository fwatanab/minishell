/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:52 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/04 14:17:35 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void	minishell(char *line, t_envval *envval)
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
	ft_execution(node, envval);
//	print_node(node);
	list_free(&tmp);
	node_free(node);
}

void	bash_loop(t_envval *envval)
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
			minishell(line, envval);
			free(line);
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_envval *envval;

	if (argc == 1)
	{
		envval = make_envval(new_envs(envp));
		bash_loop(envval);
	}	
	return (0);
}
