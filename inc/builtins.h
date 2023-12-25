/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:47:55 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/12 14:11:57 by resaito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_node	t_node;
typedef struct s_envval	t_envval;

bool			is_builtin(t_node *node);
void			exec_builtin(t_node *node, t_envval *envval);
int				cd(t_node *node, t_envval *envval);
int				echo(t_node *node);
int				export(t_node *node, t_envval *envval);
int				ft_env(t_envval *envval);
int				pwd(void);
int				unset(t_node *node, t_envval *envval);
void			ft_exit(t_node *node, t_envval *envval);

#endif
