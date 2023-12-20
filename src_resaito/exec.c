/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:39:58 by resaito           #+#    #+#             */
/*   Updated: 2023/12/19 18:43:30 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	execute_command(t_node *node, bool has_pipe, t_envval *envval)
{
	int		pipefd[2];
	pid_t	pid;

	if (has_pipe)
		ft_pipe(pipefd);
	pid = fork();
	node->pid = pid;
	if (pid < 0)
		ft_perror("fork");
	else if (pid == 0)
		child_process(node, has_pipe, envval, pipefd);
	else
	{
		signal(SIGINT, signal_fork_handler);
		signal(SIGQUIT, signal_fork_handler);
		parent_process(has_pipe, pipefd);
		return (0);
	}
	return (0);
}

// #include <stdio.h>
void	execution(t_node *node, bool is_exec_pipe, t_envval *envval)
{
	int	status;

	if (node == NONE)
		return ;
	if (node->type == N_PIPE)
	{
		execution(node->left, true, envval);
		execution(node->right, false, envval);
	}
	if (node->type == N_COMMAND)
	{
		status = dup_2_stdin(node);
		if (status == 0)
			status = dup_2_stdout(node);
		if (status != 0)
		{
			envval->status = status;
			return ;
		}
		execute_command(node, is_exec_pipe, envval);
	}
	return ;
}

void	wait_all(t_node *node, t_envval *envval)
{
	int	status;

	if (node == NONE)
		return ;
	if (node->type == N_PIPE)
	{
		wait_all(node->left, envval);
		wait_all(node->right, envval);
	}
	if (node->type == N_COMMAND)
	{
		waitpid(node->pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			envval->status = 130;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			envval->status = 131;
		else if (WIFEXITED(status))
			envval->status = WEXITSTATUS(status);
	}
	return ;
}

void	ft_execution(t_node *node, t_envval *envval)
{
	int	dupin;
	int	dupout;

	dupin = dup(STDIN_FILENO);
	dupout = dup(STDOUT_FILENO);
	if (input_redir(node, envval) == -1)
		return ;
	output_redir(node, envval);
	if (is_single_command(node) && is_builtin(node))
		exec_builtin(node, envval);
	else
	{
		execution(node, false, envval);
		close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		wait_all(node, envval);
	}
	dup2(dupin, STDIN_FILENO);
	close(dupin);
	dup2(dupout, STDOUT_FILENO);
	close(dupout);
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
