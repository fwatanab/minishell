/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/23 17:47:12 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/libft_utils.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include "lexer_parser_utils.h"

# define MINISHELL "minishell $ "
# define SPACE ' '
# define D_QUOTE '"'
# define S_QUOTE '\''
# define PYPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define REDIR_HIRE "<<"
# define REDIR_APPEND ">>"

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}	t_token_list;

typedef enum e_type
{
	NONE,
	N_COMMAND,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_REDIR_HERE,
	N_REDIR_APPEND,
	N_PIPE
}	t_type;

typedef struct s_redir
{
	enum e_type		type;
	char			**file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	enum e_type		type;
	char			*name;
	char			**args;
	struct s_redir	*redir;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//lexer parser
t_token_list	*tokenize(const char *str);
void			check_token(t_token_list *list);
t_node			*parser_start(t_token_list **list);
t_node			*parser(t_node *node, t_token_list **list, t_parse_check *key);
t_redir			*redir_parse(t_node *node, t_redir *redir, t_token_list **list, char *token);

//expansion
void	check_exp(t_node *node);

//free
void			list_free(t_token_list **list);
void			str_array_free(char **array);
void			node_free(t_node *node);
void			redir_free(t_redir *redir);

//error
void			malloc_error(void);

//resaito
char			*search_path(const char *filename);
int				execution(t_node *node, bool is_exec_pipe);
void			ft_execution(t_node *node);
int				redir_dup(t_node *node, int *pipefd);
int				indirect_exec(t_node *node, int dupout);

#endif
