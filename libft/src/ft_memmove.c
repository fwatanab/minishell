/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:25:55 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:57:20 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dst2;
	const unsigned char	*src2;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	dst2 = (unsigned char *)dst;
	src2 = (const unsigned char *)src;
	i = 0;
	if (src2 < dst2)
	{
		while (0 < n--)
			dst2[n] = src2[n];
	}
	else
	{
		while (i < n)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	return (dst2);
}
