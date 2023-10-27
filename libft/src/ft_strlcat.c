/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:44:17 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:58:14 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	if (!dst && !dstsize)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (!dstsize)
		return (len_src);
	i = 0;
	while (len_dst + i < dstsize - 1 && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	if (len_dst < dstsize)
		return (len_dst + len_src);
	return (len_src + dstsize);
}
