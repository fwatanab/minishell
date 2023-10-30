NAME	= minishell

SRCSDIR	= src/

SRCS = main.c tokenize.c check_token.c utils.c parser.c init.c print.c search_path.c

OBJS	= $(addprefix $(SRCSDIR), $(SRCS:.c=.o))

CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
RM		= rm -f

LIBFTDIR	= libft/
LIBFTNAME	= libft.a

all:$(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFTDIR)$(LIBFTNAME):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean:
	$(RM) $(OBJS) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
