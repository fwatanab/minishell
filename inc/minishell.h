/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/08 13:38:23 by resaito          ###   ########.fr       */
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
# include <fcntl.h>
# include "lexer_parser_utils.h"
# include <signal.h>

# define MINISHELL "minishell $ "
# define SPACE ' '
# define D_QUOTE '"'
# define S_QUOTE '\''
# define PYPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define REDIR_HIRE "<<"
# define REDIR_APPEND ">>"

volatile sig_atomic_t received_signal;

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next; }	t_token_list;

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
	int				fd;
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_envval
{
	t_env	*env;
	int		status;
}	t_envval;

//lexer parser
t_token_list	*tokenize(const char *str);
void			check_token(t_token_list *list);
t_node			*parser_start(t_token_list **list);
t_node			*parser(t_node *node, t_token_list **list, t_parse_check *key);
t_redir			*redir_parse(t_node *node, t_redir *redir, t_token_list **list, char *token);

//expansion
void			check_exp(t_node *node, t_envval *envval);

//signal
void			signal_handler(int sig);
void			signal_fork_handler(int sig);
void			check_status(sig_atomic_t received_signal, t_envval *envval, int fork);

//free
void			list_free(t_token_list **list);
void			str_array_free(char **array);
void			node_free(t_node *node);
void			redir_free(t_redir *redir);

//error
void			malloc_error(void);

//resaito search_path
char			*search_path(const char *filename);

// exec
void			execution(t_node *node, bool is_exec_pipe, t_envval *envval);
void			ft_execution(t_node *node, t_envval *envval);
int				child_process(t_node *node, bool has_pipe, t_envval *envval,
					int pipefd[2]);
void			parent_process(bool has_pipe, int pipefd[2]);

// redir
int				redir_dup(t_node *node);
int				indirect_exec(t_node *node);
int				heredoc_exec(t_redir *redir, t_envval *envval);
int				input_redir(t_node *node, t_envval *envval);
bool			is_type_heredoc(t_redir *redir);
bool			is_type_indirect(t_redir *redir);
int				dup_2_stdin(t_node *node);

// env
t_env			*new_envs(char **envp);
void			envadd_back(t_env **env, t_env *new);
t_env			*new_env(char *envp);
char			**make_env_strs(t_env *env);
size_t			ft_list_size(t_env *env);
void			envs_free(t_env *env);
void			envs_str_free(t_env *env, char **str);
void			env_free(t_env *env);
t_envval		*make_envval(t_env *env);

// builtin
bool			is_builtin(t_node *node);
void			exec_builtin(t_node *node, t_envval *envval);
int				cd(t_node *node, t_envval *envval);
int				echo(t_node *node);
int				export(t_node *node, t_envval *envval);
int				ft_env(t_envval *envval);
int				pwd(t_envval *envval);
int				unset(t_node *node, t_envval *envval);

// utils
void			*ft_xmalloc(size_t size);
void			ft_perror(char *str);
int				ft_pipe(int pipefd[2]);
int				print_error(char *command, char *error, int status);
bool			is_single_command(t_node *node);

#endif
