/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:52:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/21 19:10:05 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expansion.h"

void	expansion(char **array)
{
	char	*new_array;
	size_t	i;

	i = 0;
	new_array = NULL;
	while (array[i])
	{
		array[i] = expand_parameter(array[i]);
//		printf("test >%s\n", new_array);
		i++;
	}
}

void	test_exp(t_node *node)
{
	size_t	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
		expansion(node->args);
	if (node->left)
		test_exp(node->left);
	if (node->right)
		test_exp(node->right);
}
