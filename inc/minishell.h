/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/11/08 09:21:45 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
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

//free
void			list_free(t_token_list **list);
void			str_array_free(char **array);
void			node_free(t_node *node);
void			redir_free(t_redir *redir);

//error
void			malloc_error(void);

//utils
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strstr(const char *big, const char *little);
int				ft_strcmp(const char *s1, const char *s2);
char			*my_strjoin(char const *s1, char const *s2);

//resaito
char			*search_path(const char *filename);
void			ft_execution(t_node *node);

#endif
