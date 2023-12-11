/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:05:33 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 16:46:34 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

char	*ft_getenv(char *str, t_env *env)
{
	if (!str || *str == '\0')
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*update_string_with_status(t_parm *parm, char *status_str)
{
	char	*new;
	size_t	new_len;

	new_len = ft_strlen(parm->str) + ft_strlen(status_str);
	new = ft_realloc(parm->str, new_len + 1);
	if (!new)
	{
		free(parm->str);
		return (NULL);
	}
	ft_strcat(new, status_str);
	parm->str = new;
	return (parm->str);
}

int	check_question(t_parm *parm, t_envval *envval)
{
	char	*tmp;

	if (*(parm->tmp + 1) == '{' && *(parm->tmp + 2) == '?'
		&& *(parm->tmp + 3) == '}')
	{
		tmp = ft_itoa(envval->status);
		parm->str = update_string_with_status(parm, tmp);
		free(tmp);
		if (!parm->str)
			return (-1);
		parm->tmp += 4;
		return (0);
	}
	else if (*(parm->tmp + 1) == '?')
	{
		tmp = ft_itoa(envval->status);
		parm->str = update_string_with_status(parm, tmp);
		free(tmp);
		if (!parm->str)
			return (-1);
		parm->tmp += 2;
		return (0);
	}
	return (1);
}

void	check_brackets_balance(size_t *brackets, \
		char **token, char *env_name, t_parm *parm)
{
	size_t	i;

	i = 1;
	if (*brackets % 2 == 1)
	{
		env_name[0] = '\0';
		while ((*token)[i] && (*token)[i] != '}')
			i++;
		if ((*token)[i] == '}')
			i++;
		*brackets = 0;
		parm->tmp = &(*token)[i];
	}
}
