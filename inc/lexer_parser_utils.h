/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:50:56 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/11 19:15:33 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_UTILS_H
# define LEXER_PARSER_UTILS_H

# include <stdbool.h>

typedef struct s_token_list t_token_list;
typedef struct s_redir t_redir;
typedef struct s_node t_node;

typedef struct s_token_check
{
	const char	*start;
	char		*token;
	bool		d_quote;
	bool		s_quote;
}	t_token_check;

typedef struct s_parse_check
{
	char			*token;
	bool			key_type;
	bool			key_redir;
	t_token_list	*key_list;
	t_token_list	*redir_list;
}	t_parse_check;

//init
t_token_check	*checker_init(void);
t_node			*node_init(void);
void			all_node_init(t_node *node);

//parser_utils
char			*pop_token(t_token_list **list);
char			**add_array(char **array, char *token);
void			one_n_command(t_node *node);
void			check_right_node(t_node *node);

//print
void			print_list(t_token_list *list);
void			print_node(t_node *node);

#endif
