/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/12/19 12:33:05 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expansion.h"

static int	single_heredoc(int pipefd[2], t_redir *redir, t_envval *envval);

int	redir_dup(t_node *node)
{
	int	out_fd;

	if (!(node->redir != NULL && (node->redir->type == N_REDIR_OUT
				|| node->redir->type == N_REDIR_APPEND)))
		return (0);
	while (node->redir != NULL && (node->redir->type == N_REDIR_OUT
			|| node->redir->type == N_REDIR_APPEND))
	{
		if (node->redir->type == N_REDIR_OUT)
			out_fd = open(node->redir->file,
					O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
					S_IRUSR | S_IWUSR);
		else
			out_fd = open(node->redir->file,
					O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC,
					S_IRUSR | S_IWUSR);
		node->redir = node->redir->next;
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	return (0);
}

int	signal_check(void)
{
	if (g_sig_status)
		rl_done = 1;
	return (0);
}

int	heredoc_exec(t_redir *redir, t_envval *envval)
{
	int		pipefd[2];
	int		single_return;

	if (g_sig_status == 1)
		return (-2);
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	while (1)
	{
		signal(SIGINT, signal_heredoc_handler);
		signal(SIGQUIT, signal_heredoc_handler);
		rl_event_hook = signal_check;
		single_return = single_heredoc(pipefd, redir, envval);
		if (single_return == 1)
			break ;
		else if (single_return == -2)
			return (-2);
	}
	return (pipefd[0]);
}

static int	single_heredoc(int pipefd[2], t_redir *redir, t_envval *envval)
{
	char	*line;

	line = readline("> ");
	if (g_sig_status == 1)
	{
		if (g_sig_status == 1)
			free(line);
		close(pipefd[1]);
		close(pipefd[0]);
		return (-2);
	}
	if (line == NULL || ft_strcmp(line, redir->file) == 0)
	{
		free(line);
		close(pipefd[1]);
		return (1);
	}
	line = expand_parameter(line, envval);
	ft_putendl_fd(line, pipefd[1]);
	free(line);
	return (0);
}

// t_node *make_node(enum e_type node_type, char **args)
// {
//     t_node *node;

//     node = calloc(sizeof(t_node), 1);
//     node->type = node_type;
//     node->name = args[0];
//     node->args = args;
//     return (node);
// }

// t_redir *make_redir(enum e_type node_type, char **file)
// {
// 	t_redir *redir;

// 	redir = malloc(sizeof(t_redir) * 1);
// 	redir->file = file;
// 	redir->type = node_type;
// 	redir->next = NULL;
// 	return (redir);
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
//     heredoc_exec(ast->redir->file[0]);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
