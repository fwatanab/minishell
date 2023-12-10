/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:39:58 by resaito           #+#    #+#             */
/*   Updated: 2023/12/04 14:19:04 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"
#include <fcntl.h>

int	execute_command(t_node *node, bool has_pipe, t_envval *envval)
{
	int		pipefd[2];
	pid_t	pid;

	signal(SIGINT, signal_fork_handler);
	signal(SIGQUIT, signal_fork_handler);
	if (has_pipe)
		ft_pipe(pipefd);
	pid = fork();
	if (pid < 0)
		ft_perror("fork");
	else if (pid == 0)
		child_process(node, has_pipe, envval, pipefd);
	else
	{
		parent_process(has_pipe, pipefd);
		return (0);
	}
	return (0);
}

// #include <stdio.h>
int	execution(t_node *node, bool is_exec_pipe, t_envval *envval)
{	
	int	dupout;

	if (node == NONE)
		return (0);
	if (node->type == N_PIPE)
	{
		execution(node->left, true, envval);
		execution(node->right, false, envval);
	}
	if (node->type == N_COMMAND)
	{
		dup_2_stdin(node);
		execute_command(node, is_exec_pipe, envval);
	}
	return (0);
}

void	wait_all(t_node *node, t_envval *envval)
{
	if (node == NONE)
		return ;
	if (node->type == N_PIPE)
	{
		wait_all(node->left, envval);
		wait_all(node->right, envval);
	}
	if (node->type == N_COMMAND)
		wait(&(envval->status));
	return ;
}

void	ft_execution(t_node *node, t_envval *envval)
{
	int	dupin;

	dupin = dup(STDIN_FILENO);
	input_redir(node, envval);
	execution(node, false, envval);
	wait_all(node, envval);
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
// 	char *eof2[] = {"fuga", NULL};

//     ast = make_node(N_PIPE, ls);
//     ast->left = make_node(N_COMMAND, cat);
//     // ast->right = make_node(N_PIPE, ls);
//     ast->right = make_node(N_COMMAND, cat);
//     // ast->right->right = make_node(N_COMMAND, wc);

// 	redir = make_redir(N_REDIR_HERE, eof);
// 	// redir->next = make_redir(N_REDIR_IN, file3);
// 	// redir->next->next = make_redir(N_REDIR_OUT, file2);
// 	redir2 = make_redir(N_REDIR_HERE, eof2);
// 	ast->left->redir = redir;
// 	ast->right->redir = redir2;
//     ft_execution(ast);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
