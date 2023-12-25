/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:26:22 by resaito           #+#    #+#             */
/*   Updated: 2023/12/11 18:53:01 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

#define PATHNAME_SIZE 512

int	pwd(void)
{
	char	pathname[PATHNAME_SIZE];

	ft_memset(pathname, '\0', PATHNAME_SIZE);
	if (getcwd(pathname, PATHNAME_SIZE) == NULL)
		return (1);
	ft_putendl_fd(pathname, STDOUT_FILENO);
	return (0);
}
