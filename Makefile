NAME	= minishell

SRCSDIR	= src/

SRCS = main.c free.c tokenize.c check_token.c parser.c redir_parser.c parser_utils.c lexer_parser_init.c expansion.c exp_init.c expand_parameter.c expand_utils.c signal.c print.c

RE_SRCSDIR	= src_resaito/

RE_SRCS = exec.c \
			search_path.c \
			redirect_dup.c \
			input_redir.c \
			make_env.c \
			env_free.c \
			make_envval.c \
			ft_xmalloc.c \
			ft_perror.c \
			ft_pipe.c \
			execution_by_process.c \
			print_error.c \
			builtin/builtin.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/export.c \
			builtin/ft_env.c \
			builtin/pwd.c \
			builtin/unset.c \
			is_single_command.c

BUILTINS	= builtins/

B_SRCS	= exit.c

OBJS	= $(addprefix $(SRCSDIR), $(SRCS:.c=.o))

RE_OBJS	= $(addprefix $(RE_SRCSDIR), $(RE_SRCS:.c=.o))

B_OBJS	= $(addprefix $(BUILTINS), $(B_SRCS:.c=.o))

CC		= cc
CFLAGS	= -g -I$(READLINEDIR)/include #-fsanitize=address #-Wall -Wextra -Werror
RM		= rm -f
READLINEDIR    := $(shell brew --prefix readline)

LIBFTDIR	= libft/
LIBFTNAME	= libft.a

all:$(NAME)

$(NAME):$(OBJS) $(RE_OBJS) $(B_OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -L$(READLINEDIR)/lib -lreadline -lhistory -o $(NAME) $(OBJS) $(RE_OBJS) $(B_OBJS) -L$(LIBFTDIR) -lft
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFTDIR)$(LIBFTNAME):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS) $(RE_OBJS) $(B_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean:
	$(RM) $(OBJS) $(RE_OBJS) $(B_OBJS) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
