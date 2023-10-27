/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:33:18 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 09:58:39 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	size_t		i;

	str = (const char *)s;
	i = ft_strlen(s);
	i += 1;
	while (0 < i--)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	}
	return (NULL);
}
