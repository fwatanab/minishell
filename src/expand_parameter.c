/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:43:04 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:48:59 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

static char	*update_string(t_parm *parm)
{
	char	*new;

	parm->len = ft_strlen(parm->str);
	new = ft_realloc(parm->str, parm->len + 2);
	if (!new)
	{
		free(parm->str);
		free(parm);
		return (NULL);
	}
	parm->str = new;
	parm->str[parm->len] = *parm->tmp;
	parm->str[parm->len + 1] = '\0';
	parm->tmp++;
	return (parm->str);
}

static char	*parse_parameter(char *token, char *env_name, t_parm *parm)
{
	size_t	brackets;
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	brackets = 0;
	while (token[i] && (token[i] == '{' || token[i] == '}'
			|| token[i] == '_' || ft_isalnum(token[i]) == 1))
	{
		if (token[i - 1] == '$' && brackets < 1 && token[i] == '{')
			brackets++;
		else if ((brackets < 2 && 0 < brackets) && token[i] == '}')
			brackets++;
		else if (token[i] != '_' && ft_isalnum(token[i]) != 1)
			return (NULL);
		else if (token[i] == '{' || token[i] == '}')
			break ;
		else
			env_name[j++] = token[i];
		i++;
	}
	parm->tmp = &(token[i]);
	check_brackets_balance(&brackets, &token, env_name, parm);
	return (env_name);
}

static char	*get_env_var(t_parm *parm, t_envval *envval)
{
	char	*env_name;
	char	*env_var;

	if (!parm->tmp || *parm->tmp != '$')
		return (NULL);
	env_name = ft_calloc(ft_strlen(parm->tmp) + 1, sizeof(char));
	if (!env_name)
		return (NULL);
	env_name = parse_parameter(parm->tmp, env_name, parm);
	if (!env_name)
		return (NULL);
	env_var = ft_getenv(env_name, envval->env);
	if (!env_var)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(env_var);
	free(env_name);
	return (env_var);
}

static char	*expand_env_variable(t_parm *parm, t_envval *envval)
{
	char	*new;

	parm->env_var = get_env_var(parm, envval);
	if (!parm->env_var)
	{
		free(parm->str);
		free(parm);
		return (NULL);
	}
	else
	{
		parm->len = ft_strlen(parm->str) + ft_strlen(parm->env_var);
		new = ft_realloc(parm->str, parm->len + 1);
		if (!new)
		{
			free(parm->str);
			free(parm->env_var);
			free(parm);
			return (NULL);
		}
		parm->str = new;
		ft_strcat(parm->str, parm->env_var);
		free(parm->env_var);
	}
	return (parm->str);
}

char	*check_parameter(t_parm *parm, t_envval *envval)
{
	while (*parm->tmp)
	{
		if (*parm->tmp == '$' && *(parm->tmp + 1) != ' '
			&& *(parm->tmp + 1) != '\0' && *(parm->tmp + 1) != '"')
		{
			if (check_question(parm, envval) == 1)
				parm->str = expand_env_variable(parm, envval);
			if (!parm->str)
				return (NULL);
		}
		else
		{
			parm->str = update_string(parm);
			if (!parm->str)
				return (NULL);
		}
	}
	return (parm->str);
}
