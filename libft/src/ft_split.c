/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:53:38 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:57:52 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	**all_free(char	**str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	*f_strndup(char const *s, size_t n)
{
	char	*r;
	size_t	i;

	i = 0;
	r = (char *)malloc(sizeof(char) * (n + 1));
	if (r == NULL)
		return (NULL);
	while (i < n)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

static size_t	check_match(char const s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static size_t	count_malloc_size(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (check_match(s[i], c) == 1)
			i++;
		j = 0;
		while ((check_match(s[i], c) == 0) && (s[i]))
		{
			j++;
			i++;
		}
		if (j)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	mallc_size;
	char	**str;
	size_t	i;
	size_t	j;

	mallc_size = count_malloc_size(s, c);
	str = (char **)malloc(sizeof(char *) * (mallc_size + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (j < mallc_size)
	{
		i = 0;
		while (check_match(*s, c) == 1)
			s++;
		while (check_match(s[i], c) == 0 && s[i])
			i++;
		str[j] = f_strndup(s, i);
		if (str[j] == NULL)
			return (all_free(str));
		s += i;
		j++;
	}
	str[j] = NULL;
	return (str);
}
