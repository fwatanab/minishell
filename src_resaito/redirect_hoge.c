/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:05:49 by resaito           #+#    #+#             */
/*   Updated: 2023/11/09 15:06:47 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 512

int	redirect_exec(t_node *node)
{
	int		stdout_fd;
	char	*file_name;

	// 変数定義
	// 変数初期化
	stdout_fd = 0;
	// ファイルのオープン
	stdout_fd = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (stdout_fd == -1) // ファイルオープン失敗
	{
		printf("ファイルオープンエラー\n");
		return (1);
	}
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	execve(node->name, node->args, NULL);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdout_fd);
	return (0);
}

int	indirect_exec(t_node *node)
{
	int		stdin_fd;
	char	*file;

	stdin_fd = 0;
	stdin_fd = open(file, O_RDONLY);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	execve(node->name, node->args, NULL);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	return (0);
}
