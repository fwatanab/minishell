/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:52 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/27 17:04:01 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_args(char *line)
{
	char	**input;

	input = ft_split(line, SPACE);
	if (!input)
		return (1);
	return (0);
}

int	syntax_analysis(char *line)
{
	t_token_list	*head;
	t_node			*node;

	head = NULL;
	head = tokenize(line, head);
	if (!head)
		return (1);
	check_token(head);
	print_list(head);
	node = parser_start(&head);
	return (0);
}

void	bash_loop(void)
{
	char	*line;
	int		flag;

	flag = 0;
	while (flag == 0)
	{
		line = readline(MINISHELL);
		if (!line)
			flag = 1;
		else if (line[0] == '\0')
			free(line);
		else
		{
			add_history(line);
			if (syntax_analysis(line) == 1)
				flag = 1;
			free(line);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		bash_loop();
	return (0);
}
