/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/31 01:44:25 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <stdbool.h>

# define MINISHELL "minishell $ "
# define SPACE ' '
# define D_QUOTE '"'
# define S_QUOTE '\''
# define PYPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define REDIR_HIRE "<<"
# define REDIR_APPEND ">>"

typedef struct s_token_check
{
	const char	*start;
	char		*token;
	bool		d_quote;
	bool		s_quote;
}	t_token_check;

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}	t_token_list;

typedef struct s_parse_check
{
	char			*token;
	bool			key_type;
	bool			key_redir;
	t_token_list	*key_list;
	t_token_list	*redir_list;
}	t_parse_check;

typedef enum e_type
{
	N_COMMAND,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_REDIR_HERE,
	N_REDIR_APPEND,
	N_PIPE
}	t_type;

typedef struct s_node
{
	enum e_type		type;
	char			*name;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//tokenize & parser
t_token_list	*tokenize(const char *str);
void			check_token(t_token_list *list);
t_node			*parser_start(t_token_list **list);
t_node			*parser(t_node *node, t_token_list **list, t_parse_check *key);

//init
t_token_check	*checker_init(void);
t_node			*node_init(void);
void			all_node_init(t_node *node);

//free
void			list_free(t_token_list **list);
void			str_array_free(char **array);
void			node_free(t_node *node);

//malloc error
void			malloc_error(void);

//utils
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strstr(const char *big, const char *little);
int				ft_strcmp(const char *s1, const char *s2);
char			*my_strjoin(char const *s1, char const *s2);

//print
void			print_list(t_token_list *list);
void			print_node(t_node *node);
void			print_tree(t_node *node, int depth);
void			print_syntax_tree(t_node *node, int depth);

//resaito
char			*search_path(const char *filename);
void			ft_execution(t_node *node);

#endif
