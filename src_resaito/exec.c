/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:39:58 by resaito           #+#    #+#             */
/*   Updated: 2023/11/16 17:05:29 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	execute_command(t_node *node, bool has_pipe)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*line;

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
		redir_dup(node, pipefd);
		execve(node->name, node->args, NULL);
		perror(node->name);
		return (-1);
	}
	else
	{
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
	int	dupout;
	char *line;

	if (node == NONE)
		return (0);
	indirect_exec(node, dupout);
	if (node->type == N_PIPE)
	{
		execution(node->left, true);
		execution(node->right, false);
	}
	if (node->type == N_COMMAND)
	{
		execute_command(node, is_exec_pipe);
	}
	return (0);
}

void wait_all(t_node *node)
{
	int status;

	if (node == NONE)
		return ;
	if (node->type == N_PIPE)
	{
		wait_all(node->left);
		wait_all(node->right);
	}
	if (node->type == N_COMMAND)
		wait(&status);
	return ;
}

void	ft_execution(t_node *node)
{
	int dupin;

	dupin = dup(STDIN_FILENO);
	execution(node, false);
	system("leaks -q minishell");
	wait_all(node);
	// system("leaks -q minishell");
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

// t_redir *make_redir(enum e_type node_type, char **file)
// {
// 	t_redir *redir;

// 	redir = malloc(sizeof(t_redir) * 1);
// 	redir->file = file;
// 	redir->type = node_type;
// 	redir->next = NULL;
// 	return redir;
// }

// int main()
// {
//     t_node *ast;
// 	t_redir *redir;
// 	t_redir *redir2;
//     // char *args[] = {"/usr/bin/wc", "-l", NULL};
//     // char *args2[] = {"/bin/cat", NULL};
//     // char *args3[] = {"/usr/bin/grep", "hoge", NULL};
//     char *ls[] = {"/bin/ls", NULL};
//     char *cat[] = {"/bin/cat", NULL};
//     char *wc[] = {"/usr/bin/wc", "-l", NULL};
//     char *grep[] = {"/usr/bin/grep", "hoge", NULL};
// 	char *file[] = {"hoge.txt", NULL};
// 	char *file2[] = {"fuga.txt", NULL};
// 	char *file3[] = {"piyo.txt", NULL};
// 	char *eof[] = {"hoge", NULL};

//     // ast = make_node(N_PIPE, ls);
//     ast = make_node(N_COMMAND, cat);
//     // ast->right = make_node(N_PIPE, ls);
//     // ast->right = make_node(N_COMMAND, grep);
//     // ast->right->right = make_node(N_COMMAND, wc);

// 	redir = make_redir(N_REDIR_HERE, eof);
// 	// redir->next = make_redir(N_REDIR_IN, file3);
// 	// redir->next->next = make_redir(N_REDIR_OUT, file2);
// 	ast->redir = redir;
// 	// redir->next = redir2;
//     ft_execution(ast);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
