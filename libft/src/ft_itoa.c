/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:28:28 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:56:17 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	count(int n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i - 1);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		n_size;
	long int	n1;

	n1 = n;
	n_size = count(n);
	if (n < 0)
	{
		n1 *= -1;
		n_size++;
	}
	str = (char *)malloc(sizeof(char) * (n_size + 1));
	if (str == NULL)
		return (NULL);
	str[n_size] = '\0';
	while (n_size--)
	{
		str[n_size] = n1 % 10 + '0';
		n1 /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
