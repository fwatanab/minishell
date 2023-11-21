/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:43:04 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/21 19:21:13 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expansion.h"

t_parm	*parameter_init(void)
{
	t_parm	*new;

	new = (t_parm *)malloc(sizeof(t_parm));
	if (!new)
		return (NULL);
	new->tmp = NULL;
	new->token = NULL;
	new->env_name = NULL;
	return (new);
}

char	*parse_parameter(char *token)
{
	char	*str;
	size_t	brackets;
	size_t	i;
	size_t	j;

	printf(" %s\n", token);
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

char	*expand_parameter(char *token)
{
	t_parm	*parm;
	char	*env_var;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init();
	if (!parm)
		return (token);
	parm->tmp = token;
	while (*parm->tmp)
	{
		if (*parm->tmp == '$')
		{
			parm->env_name = parse_parameter(parm->tmp);
			if (!parm->env_name)
				return (token);
			env_var = getenv(parm->env_name);
			if (!env_var)
				env_var = ft_strdup("");
			else
				env_var = ft_strdup(env_var);
			return (env_var);
		}
		parm->tmp++;
	}
	free(parm);
	return (token);
}
