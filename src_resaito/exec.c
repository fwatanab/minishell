/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:39:58 by resaito           #+#    #+#             */
/*   Updated: 2023/11/02 17:58:34 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_node *node, bool has_pipe)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (has_pipe)
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe");
			exit(-1);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(-1);
	}
	else if (pid == 0)
	{
		if (has_pipe)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		execve(node->name, node->args, NULL);
		perror(node->name);
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (has_pipe)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		return (0);
	}
}

// #include <stdio.h>
int	execution(t_node *node, bool is_exec_pipe)
{	
	// FILE *fp = fopen("hoge.txt", "a");
	// fprintf(fp, "type: %d\n", node->type);
	// fprintf(fp, "name: %s\n", node->name);
	// fprintf(fp, "=========AAA: %s\n", node->name);
	if (node == NULL)
		return (0);
	if (node->type == N_PIPE)
	{
		// fprintf(fp, "=========BBB: %s\n", node->name);
		execution(node->left, true);
		execution(node->right, false);
	}
	// fprintf(fp, "=========CCC: %s\n", node->name);
	if (node->type == N_COMMAND)
		execute_command(node, is_exec_pipe);
	return (0);
}

void	ft_execution(t_node *node)
{
	int dupin;

	dupin = dup(STDIN_FILENO);
	execution(node, false);
	dup2(dupin, STDIN_FILENO);
	close(dupin);
}

// bool	has_pipe(t_node *node)
// {
// 	if (node->type == N_PIPE)
// 		return (true);
// 	return (false);
// }

// t_node *make_node(enum e_type node_type, char **args)
// {
//     t_node *node;

//     node = calloc(sizeof(t_node), 1);
//     node->type = node_type;
//     node->name = args[0];
//     node->args = args;
//     return node;
// }

// int main()
// {
//     t_node *ast;
//     // char *args[] = {"/usr/bin/wc", "-l", NULL};
//     // char *args2[] = {"/bin/cat", NULL};
//     // char *args3[] = {"/usr/bin/grep", "hoge", NULL};
//     char *ls[] = {"/bin/ls", NULL};
//     char *cat[] = {"/bin/cat", NULL};
//     char *wc[] = {"/usr/bin/wc", "-l", NULL};
//     char *grep[] = {"/usr/bin/grep", "hoge", NULL};

//     ast = make_node(N_PIPE, ls);
//     ast->left = make_node(N_COMMAND, ls);
//     ast->right = make_node(N_PIPE, ls);
//     ast->right->left = make_node(N_COMMAND, grep);
//     ast->right->right = make_node(N_COMMAND, wc);
//     ft_execution(ast, false);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
