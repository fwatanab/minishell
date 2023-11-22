/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:43:04 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/22 22:56:44 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

t_parm	*parameter_init(char *token)
{
	t_parm	*new;

	new = (t_parm *)malloc(sizeof(t_parm));
	if (!new)
		return (NULL);
	new->tmp = token;
	new->str = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->str[0] = '\0';
	new->new_len = 0;
	return (new);
}

char	*parse_parameter(char *token)
{
	char	*str;
	size_t	brackets;
	size_t	i;
	size_t	j;

	if (!token || token[0] != '$')
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(token));
	if (!str)
		return (NULL);
	i = 1;
	j = 0;
	brackets = 0;
	while (token[i] && token[i] != ' ' && token[i] != '"')
	{
		if (brackets < 1 && token[i] == '{')
			brackets++;
		else if (brackets < 2 && token[i] == '}')
			brackets++;
		else
			str[j++] = token[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*change_env_var(char *token)
{
	char	*env_name;
	char	*env_var;

	env_name = parse_parameter(token);
	if (!env_name)
		return (NULL);
	env_var = getenv(env_name);
	if (!env_var)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(env_var);
	return (env_var);
}

char	*expand_parameter(char *token)
{
	t_parm	*parm;
	char	*value;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init(token);
	if (!parm)
		return (token);
	while (*parm->tmp) {
		if (*parm->tmp == '$')
		{
			parm->env_var = change_env_var(parm->tmp);
			if (!parm->env_var)
			{
				free(parm->str);
				free(parm);
				return (token);
			}
			else
			{
				parm->new_len = ft_strlen(parm->str) + ft_strlen(parm->env_var);
				char	*new = ft_realloc(parm->str, parm->new_len + 1);
				if (!new)
				{
					free(parm->str);
					free(parm->env_var);
					free(parm);
					return token;
				}
				parm->str = new;
				ft_strcat(parm->str, parm->env_var);
				free(parm->env_var);
			}
			while (*parm->tmp && *parm->tmp != '"' && *parm->tmp != ' ')
				parm->tmp++;
		}
		else
		{
			size_t len = ft_strlen(parm->str);
			char *new = ft_realloc(parm->str, len + 2);
			if (!new)
			{
				free(parm->str);
				free(parm);
				return token;
			}
			parm->str = new;
			parm->str[len] = *parm->tmp;
			parm->str[len + 1] = '\0';
			parm->tmp++;
		}
	}
	value = ft_strdup(parm->str);
	free(parm->str);
	free(parm);
	return (value);
}
