/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:32:49 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:55:11 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static long long int	cast_cheek(const char *str, size_t i, long long int f)
{
	long long int	s;

	s = 0;
	while (str[i])
	{
		if (f == -1 && (LONG_MIN / -10 < s
				|| (s == LONG_MIN / -10 && '0' - (LONG_MIN % -10) < str[i])))
			return (LONG_MIN);
		else if (f == 1 && (LONG_MAX / 10 < s
				|| (s == LONG_MAX / 10 && '0' + (LONG_MAX % 10) < str[i])))
			return (LONG_MAX);
		if ('0' <= str[i] && str[i] <= '9')
			s = s * 10 + str[i] - '0';
		else
			return (s);
		i++;
	}
	return (s);
}

int	ft_atoi(const char *str)
{
	long long int	s;
	long long int	f;
	size_t			i;

	i = 0;
	f = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		f = -1;
		i++;
	}
	if (str[i] == '+')
	{
		if (f == -1)
			return (0);
		i++;
	}
	s = cast_cheek(str, i, f);
	return ((int)(s * f));
}
