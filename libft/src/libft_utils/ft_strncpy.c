/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:53:56 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:53:57 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft_utils.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (!src)
		return (dst);
	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}
