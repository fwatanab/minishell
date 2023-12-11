/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:53:22 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:53:23 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft_utils.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;
	size_t	copy_size;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(new_size, 1));
	new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
		return (NULL);
	old_size = ft_strlen(ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
