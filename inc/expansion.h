/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:53:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/22 06:14:07 by fwatanab         ###   ########.fr       */
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

typedef struct s_quote_status
{
	bool	d_quote;
	bool	s_quote;
	size_t	len;
	char	*result;
	size_t	i;
}	t_quote_status;

//init
t_parm			*parameter_init(char *token);

char			*check_command(char *str, t_node *node, t_envval *envval);
char			*expand_parameter(char *token, t_envval *envval);
char			*delete_quote(char *token);
char			*check_parameter(t_parm *parm, t_envval *envval);
int				check_question(t_parm *parm, t_envval *envval);
char			*ft_getenv(char *str, t_env *env);
char			*update_string_with_status(t_parm *parm, char *status_str);
t_quote_status	*quote_status_init(char *token);
void			check_brackets_balance(size_t *brackets, char **token, \
		char *env_name, t_parm *parm);
int				check_redir(t_node *node, t_envval *envval);

#endif
