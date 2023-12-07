/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:53:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/07 23:18:07 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

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

char	*check_parameter(t_parm *parm, char *token, t_envval *envval);
int		check_question(t_parm *parm, char *token, t_envval *envval);
char	*update_string_with_status(t_parm *parm, char *status_str);
void	check_brackets_balance(size_t *brackets, char **token, char *env_name, t_parm *parm);

#endif
