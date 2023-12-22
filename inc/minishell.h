/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resaito <resaito@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/12/18 18:32:25 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../inc/builtins.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/libft_utils.h"
# include "lexer_parser_utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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

extern int				g_sig_status;

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}						t_token_list;

typedef enum e_type
{
	NONE,
	N_COMMAND,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_REDIR_HERE,
	N_REDIR_APPEND,
	N_PIPE
}						t_type;

typedef struct s_redir
{
	enum e_type			type;
	char				*file;
	int					fd;
	struct s_redir		*next;
}						t_redir;

typedef struct s_node
{
	enum e_type			type;
	char				*name;
	char				**args;
	struct s_redir		*redir;
	struct s_node		*left;
	struct s_node		*right;
	pid_t				pid;
}						t_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_envval
{
	t_env				*env;
	int					status;
}						t_envval;

//lexer parser
t_token_list			*tokenize(const char *str);
void					check_token(t_token_list *list);
t_node					*parser_start(t_token_list **list);
t_node					*parser(t_node *node, t_token_list **list,
							t_parse_check *key);
t_redir					*redir_parse(t_redir *redir, \
						t_token_list **list, char *token);

//expansion
int						check_exp(t_node *node, t_envval *envval);

//signal
void					signal_handler(int sig);
void					signal_fork_handler(int sig);
void					signal_heredoc_handler(int sig);
void					check_status(t_envval *envval);
void					check_fork_status(t_envval *envval);

//free
void					list_free(t_token_list **list);
void					str_array_free(char **array);
void					node_free(t_node *node);
void					redir_free(t_redir *redir);

//error
void					malloc_error(void);
int						is_only_space(const char *str, t_envval *envval);

//resaito search_path
char					*search_path(const char *filename, t_env *env);

// exec
void					execution(t_node *node, bool is_exec_pipe,
							t_envval *envval);
void					ft_execution(t_node *node, t_envval *envval);
int						child_process(t_node *node, bool has_pipe,
							t_envval *envval, int pipefd[2]);
void					parent_process(bool has_pipe, int pipefd[2]);
bool					able_exec(char *filepath);

// redir
int						redir_dup(t_node *node);
int						indirect_exec(t_node *node);
int						heredoc_exec(t_redir *redir, t_envval *envval);
int						input_redir(t_node *node, t_envval *envval);
int						output_redir(t_node *node, t_envval *envval);
bool					is_type_redirect(t_redir *redir);
bool					is_type_append(t_redir *redir);
bool					is_type_heredoc(t_redir *redir);
bool					is_type_indirect(t_redir *redir);
int						dup_2_stdin(t_node *node);
int						dup_2_stdout(t_node *node);
bool					able_read(char *filepath);
bool					able_write(char *filepath);

// env
t_env					*new_envs(char **envp);
void					envadd_back(t_env **env, t_env *new);
t_env					*new_env(char *envp);
char					**make_env_strs(t_env *env);
size_t					ft_list_size(t_env *env);
void					envs_free(t_env *env);
void					envs_str_free(t_env *env, char **str);
void					env_free(t_env *env);
t_envval				*make_envval(t_env *env);
bool					is_name(char *str);

// utils
void					*ft_xmalloc(size_t size);
void					ft_perror(char *str);
int						ft_pipe(int pipefd[2]);
int						print_error(char *command, char *error, int status);
bool					is_single_command(t_node *node);
int						get_exit_code(int n);

#endif
