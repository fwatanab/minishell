/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:53:47 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:53:48 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft_utils.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (!src)
		return (dst);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i++] = '\0';
	return (dst);
}
