/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:47:55 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 20:01:54 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_node	t_node;
typedef struct s_envval	t_envval;

bool			is_builtin(t_node *node);
void			exec_builtin(t_node *node, t_envval *envval);
int				cd(t_node *node, t_envval *envval);
int				echo(t_node *node);
int				export(t_node *node, t_envval *envval);
int				ft_env(t_envval *envval);
int				pwd(t_envval *envval);
int				unset(t_node *node, t_envval *envval);
void			ft_exit(t_node *node, t_envval *envval);

#endif
