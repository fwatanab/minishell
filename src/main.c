/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:52 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/22 19:21:32 by fwatanab         ###   ########.fr       */
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
	node = parser_start(&list);
	list_free(&tmp);
	if (check_exp(node, envval) == 1)
	{
		node_free(node);
		return ;
	}
	print_node(node);
	ft_execution(node, envval);
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
		check_fork_status(envval);
		line = readline(MINISHELL);
		check_status(envval);
		if (!line)
		{
			write(1, "exit\n", 5);
			exit(envval->status);
			break ;
		}
		else if (!(line[0] == '\0' || is_only_space(line, envval) == 0))
		{
			add_history(line);
			minishell(line, envval);
		}
		free(line);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_envval	*envval;

	if (argc == 1 && argv)
	{
		envval = make_envval(new_envs(envp));
		bash_loop(envval);
		envs_free(envval->env);
		free(envval);
	}	
	return (0);
}
