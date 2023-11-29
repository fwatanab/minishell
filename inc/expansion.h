/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:53:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/29 17:35:15 by resaito          ###   ########.fr       */
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
	char		*tmp;
	char		*str;
	char		*env_var;
	char		*end;
	size_t		len;
}	t_parm;

//init
t_parm	*parameter_init(char *token);

char	*check_parameter(t_parm *parm, char *token);
char	*expand_parameter(char *token);

#endif
