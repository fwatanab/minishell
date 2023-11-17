/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 03:53:40 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/15 13:40:52 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdbool.h>

typedef struct s_brace
{
	char		**token;
	const char	*p;
	char		*start;
	bool		flag;
	char		*tmp;
	char		*expand;
	char		pre[1020];
	char		post[1020];
}	t_brace;

void	brace_exp(char *str);

#endif
