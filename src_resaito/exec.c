/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:39:58 by resaito           #+#    #+#             */
/*   Updated: 2023/10/31 16:11:36 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	has_pipe(t_node *node);

void	execute_command(char *cmd_name, char **args, int input_fd,
		int output_fd)
{
	if (fork() == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		execve(cmd_name, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		while (wait(NULL) > 0)
			;
}

void	ft_execution(t_node *node)
{
	if (node->type == N_COMMAND)
		execute_command(node->name, node->args, STDIN_FILENO, STDOUT_FILENO);
	// if (has_pipe(node))
	// 	printf("has pipe\n");
	// else
	// 	printf("doesn't have pipe\n");
}

bool	has_pipe(t_node *node)
{
	if (node->type == N_PIPE)
		return (true);
	node = node->right;
	return (false);
}

// int	main(void)
// {
// 	int pipefd1[2], pipefd2[2];

// 	if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	execute_command("command1", STDIN_FILENO, pipefd1[1]);
// 	close(pipefd1[1]);

// 	execute_command("command2", pipefd1[0], pipefd2[1]);
// 	close(pipefd1[0]);
// 	close(pipefd2[1]);

// 	execute_command("command3", pipefd2[0], STDOUT_FILENO);
// 	close(pipefd2[0]);

// 	// すべての子プロセスが終了するのを待つ
// 	while (wait(NULL) > 0)
// 		;

// 	return (0);
// }
