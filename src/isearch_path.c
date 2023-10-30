/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isearch_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:40:54 by resaito           #+#    #+#             */
/*   Updated: 2023/10/30 16:38:18 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*search_path(const char *filename);
char	*able_to_access(char *path);

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH");
	while (value)
	{
		ft_bzero(path, PASS_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, (end + 1) - value);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (able_to_access(path));
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

char	*able_to_access(char *path)
{
	char	*dup;

	dup = ft_strdup(path);
	if (dup == NULL)
		return (NULL);
	return (dup);
}

// int	main(int ac, char **av, char **envp)
// {
//     (void)ac;
//     (void)av;
//     char *args[] = {search_path("ls"), "-la", NULL};
// 	execve(args[0], args, envp);
// }
