/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:43:04 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/22 20:55:09 by fwatanab         ###   ########.fr       */
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

//char	*expand_parameter(char *token)
//{
//	t_parm	*parm;
//	char	*value;
//	char	*tmp;
//
//	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
//		return (token);
//	parm = parameter_init();
//	if (!parm)
//		return (token);
//	parm->tmp = token;
//	value = token;
//	tmp = "";
//	while (*parm->tmp)
//	{
//		if (*parm->tmp == '$')
//		{
//			parm->env_var = change_env_var(parm->tmp);
//			if (!parm->env_var)
//				return (value);
//			else
//			{
//				char	*new = malloc(sizeof(char) * (ft_strlen(token) + ft_strlen(parm->env_var)));
//				ft_strcpy(new, tmp);
//				ft_strcpy(new, parm->env_var);
//				new += ft_strlen(parm->env_var);
//				tmp = new;
//			}
//			while (*parm->tmp && *parm->tmp != '"' && *parm->tmp != ' ')
//				parm->tmp++;
//		}
//		else
//		{
//			*tmp = *parm->tmp;
//			parm->tmp++;
//		}
//		tmp++;
//	}
//	free(parm);
//	return (value);
//}

char	*expand_parameter(char *token) {
	t_parm	*parm;
	char	*value;
	char	*tmp;
	size_t	new_len;

	if (!token || (token[0] == '\'' && token[ft_strlen(token) - 1] == '\''))
		return (token);
	parm = parameter_init();
	if (!parm)
		return (token);
	parm->tmp = token;
	tmp = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!tmp) {
		free(parm);
		return token;
	}
	tmp[0] = '\0';
	while (*parm->tmp) {
		if (*parm->tmp == '$') {
			parm->env_var = change_env_var(parm->tmp);
			if (!parm->env_var) {
				free(tmp);
				free(parm);
				return (token);
			} else {
				new_len = ft_strlen(tmp) + ft_strlen(parm->env_var);
				char	*new = ft_realloc(tmp, new_len + 1);
				if (!new) {
					free(tmp);
					free(parm->env_var);
					free(parm);
					return token;
				}
				tmp = new;
				ft_strcat(tmp, parm->env_var);
				free(parm->env_var);
			}
			while (*parm->tmp && *parm->tmp != '"' && *parm->tmp != ' ')
				parm->tmp++;
		} else {
			size_t len = ft_strlen(tmp);
			char *new = ft_realloc(tmp, len + 2);
			if (!new) {
				free(tmp);
				free(parm);
				return token;
			}
			tmp = new;
			tmp[len] = *parm->tmp;
			tmp[len + 1] = '\0';
			parm->tmp++;
		}
	}
	value = ft_strdup(tmp);
	free(tmp);
	free(parm);
	return (value);
}
