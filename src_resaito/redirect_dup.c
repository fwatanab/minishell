/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/11/16 17:49:53 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>

int	redir_dup(t_node *node)
{
	int out_fd;

	if (!(node->redir != NULL && (node->redir->type == N_REDIR_OUT
				|| node->redir->type == N_REDIR_APPEND)))
		return (0);
	while (node->redir != NULL && (node->redir->type == N_REDIR_OUT
			|| node->redir->type == N_REDIR_APPEND))
	{
		if (node->redir->type == N_REDIR_OUT)
			out_fd = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR);
		else
			out_fd = open(node->redir->file[0],
					O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, S_IRUSR | S_IWUSR);
		node->redir = node->redir->next;
	}
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	return (0);
}

int	indirect_exec(t_node *node)
{
	t_redir *redir;
	int 	dupin;

	redir = node->redir;
	if (!(redir != NULL && redir->type == N_REDIR_IN))
		return (0);
	while (redir != NULL && (redir->type == N_REDIR_IN))
	{
		if (redir->type == N_REDIR_IN)
			dupin = open(redir->file[0], O_RDONLY);
		redir = redir->next;
	}
	dup2(dupin, STDIN_FILENO);
	close(dupin);
	return (0);
}

int	heredoc_exec(t_node *node)
{
	char	*line;
	int		pipefd[2];

	if (!(node->redir != NULL && node->redir->type == N_REDIR_HERE))
		return (0);
	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		exit(-1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, node->redir->file[0], ft_strlen(node->redir->file[0])) == 0)
		{
			free(line);
			close(pipefd[1]);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (pipefd[1]);
}

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
//     heredoc_exec(ast->redir->file[0]);
//     // command_exec(args2, true);
//     // command_exec(args3, false);
//     // wait(NULL);
//     // wait(NULL);
// }
