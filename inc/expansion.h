/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:53:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/22 22:49:33 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/inc/libft.h"
# include "../libft/inc/libft_utils.h"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_parm
{
	char		*token;
	char		*tmp;
	char		*str;
	char		*env_var;
	char		*value;
	size_t		new_len;
}	t_parm;

char	*expand_parameter(char *token);

#endif
