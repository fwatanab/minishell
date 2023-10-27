/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:39:05 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:57:16 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *str, const void *src, size_t n)
{
	unsigned char		*str2;
	const unsigned char	*src2;
	size_t				i;

	str2 = (unsigned char *)str;
	src2 = (const unsigned char *)src;
	if (!str && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str2[i] = src2[i];
		i++;
	}
	return (str2);
}
