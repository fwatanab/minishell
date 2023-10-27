/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 01:07:32 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:59:01 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line_bonus.h"

char	*keep_line(char *keep)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(keep) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (keep[i])
		str[j++] = keep[i++];
	str[j] = '\0';
	free(keep);
	return (str);
}

char	*get_line(char *keep)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		str[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*read_fd(int fd, char *keep)
{
	char	*buff;
	ssize_t	byte;
	size_t	i;

	i = 0;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte = 1;
	while (!ft_strchr(keep, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		keep = f_strjoin(keep, buff, i);
	}
	free(buff);
	return (keep);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*keep[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep[fd] = read_fd(fd, keep[fd]);
	if (!keep[fd])
		return (NULL);
	line = get_line(keep[fd]);
	keep[fd] = keep_line(keep[fd]);
	return (line);
}
