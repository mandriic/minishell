


R42LFLAG = -L/Users/angalsty/.brew/opt/readline/lib
R42IFLAG = -I/Users/angalsty/.brew/opt/readline/include
R42LFLAGM = -L/opt/homebrew/opt/readline/lib 
R42IFLAGM = -I/opt/homebrew/opt/readline/include
R42LFLAGU = -L/usr/share/readline 
R42IFLAGU = -I/usr/include/readline
INCS     = inc/
BIN_PATH = bin/
SRCS_PATH = src/
LIBFT_PATH = libft/
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
SRCS = fn_list.c fn_builtins.c fn_main_readline.c fnadd_free.c fnadd_libftmod.c fn_additional.c fn_cleaning.c fn_getenvs.c \
fn_mask.c fn_pip_splt_trim.c fn_vars.c main.c fn_redirs.c fn_create_data.c mi_execve.c fn_cd.c signal.c

CC       = gcc

OBJS     = $(SRCS:%.c=$(BIN_PATH)%.o)

CFLAGS   = -g -O0#-Wall -Wextra -Werror

NAME     = minishell

RM       = rm -f

$(BIN_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS) $(R42IFLAG) #-I/opt/homebrew/opt/readline/include

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -I$(INCS) -o $(NAME) $(R42LFLAG) $(R42IFLAG) -lreadline #-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re