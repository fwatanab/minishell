/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:29:34 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/17 09:49:59 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/expansion.h"

static size_t	brace_count(char *str)
{
	size_t	i;
	bool	d_quote;
	size_t	right;
	size_t	left;

	i = 0;
	right = 0;
	left = 0;
	d_quote = false;
	while (str[i])
	{
		if (!d_quote && str[i] == '"')
			d_quote = true;
		else if (d_quote && str[i] == '"')
			d_quote = false;
		if (!d_quote && str[i] == '{')
			left++;
		if (!d_quote && str[i] == '}')
			right++;
		i++;
	}
	if (left != right)
		return (0);
	return (left);
}

t_brace	*brace_init(char *str)
{
	t_brace *new;

	if (!str)
		return (NULL);
	new = (t_brace *)malloc(sizeof(t_brace));
	if (!new)
		return (NULL);
	new->p = str;
	new->start = NULL;
	new->flag = false;
	new->tmp = NULL;
	return (new);
}

char	*split_to_join(char *pre, char *expand, char *post)
{
	char	*token;
	size_t	len;
	size_t	i;
	size_t	j;

	len = (ft_strlen(pre) + ft_strlen(expand) + ft_strlen(post));
	printf("len %zu\n", len);
	token = (char *)malloc(sizeof(len + 1));
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	while (pre[j] && i < len)
		token[i++] = pre[j++];
	j = 0;
	while (expand[j] && i < len)
		token[i++] = expand[j++];
	j = 0;
	while (post[j] && i < len)
		token[i++] = post[j++];
	token[i] = '\0';
	return (token);
}

void	brace_exp(char *str)
{
	t_brace	*brace;
	char	*token;

	if (!str)
		return ;
	brace = brace_init(str);
	while (*brace->p)
	{
		if (*brace->p == '{' && !brace->flag)
		{
			brace->flag = true;
			brace->start = (char *)brace->p + 1;
		}
		else if (*brace->p == '}' && brace->flag)
		{
			brace->flag = false;
			brace->expand = (char *)malloc(sizeof((brace->p - brace->start) + 1));
			if (!brace->expand)
			{
				free(brace);
				return ;
			}
			ft_strncpy(brace->expand, brace->start, brace->p - brace->start);
			brace->tmp = (char *)brace->p + 1;
			while (*brace->tmp && *brace->tmp != '{')
			{
				ft_strncat(brace->post, brace->tmp, 1);
				brace->tmp++;
			}
			brace->token = ft_split(brace->expand, ',');
			free(brace->expand);
			if (!brace->token)
			{
				str_array_free(brace->token);
				return ;
			}
			token = NULL;
			while (*brace->token)
			{
				brace->tmp = split_to_join(brace->pre, *brace->token, brace->post);
				if (token)
					token = my_strjoin(token, " ");
				token = my_strjoin(token, brace->tmp);
				brace->token++;
			}
			printf("token->%s\n", token);
		}
		else if (!brace->flag)
			ft_strncat(brace->pre, brace->p, 1);
		brace->p++;
	}
//	printf("pre %s\n", brace->pre);
//	printf("str2 %s\n", expand);
//	printf("post %s\n", brace->post);
}
