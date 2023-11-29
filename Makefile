NAME	= minishell

SRCSDIR	= src/

SRCS = main.c free.c tokenize.c check_token.c parser.c redir_parser.c parser_utils.c lexer_parser_init.c expansion.c exp_init.c expand_parameter.c signal.c print.c

RE_SRCSDIR	= src_resaito/

RE_SRCS = exec.c \
			search_path.c \
			redirect_dup.c

OBJS	= $(addprefix $(SRCSDIR), $(SRCS:.c=.o))

RE_OBJS	= $(addprefix $(RE_SRCSDIR), $(RE_SRCS:.c=.o))

CC		= cc
CFLAGS	= -g -I$(READLINEDIR)/include #-Wall -Wextra -Werror
RM		= rm -f
READLINEDIR    := $(shell brew --prefix readline)

LIBFTDIR	= libft/
LIBFTNAME	= libft.a

all:$(NAME)

$(NAME):$(OBJS) $(RE_OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -L$(READLINEDIR)/lib -lreadline -lhistory -o $(NAME) $(OBJS) $(RE_OBJS) -L$(LIBFTDIR) -lft
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFTDIR)$(LIBFTNAME):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS) $(RE_OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean:
	$(RM) $(OBJS) $(RE_OBJS) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
