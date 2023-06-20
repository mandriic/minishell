INCS     = inc/
BIN_PATH = bin/
SRCS_PATH = src/
LIBFT_PATH = libft/
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
SRCS = fn_list.c fn_builtins.c fn_main_readline.c fnadd_free.c fnadd_libftmod.c fn_additional.c fn_cleaning.c fn_getenvs.c \
fn_mask.c fn_pip_splt_trim.c fn_vars.c main.c fn_redirs.c fn_create_data.c mi_execve.c fn_cd.c signal.c
CC       = gcc
OBJS     = $(SRCS:%.c=$(BIN_PATH)%.o)
CFLAGS   = #-Wall -Wextra -Werror
NAME     = minishell
RM       = rm -f
$(BIN_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS) -I/sgoinfre/goinfre/Perso/angalsty/homebrew/opt/readline/include
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -I$(INCS) -o $(NAME) -L/sgoinfre/goinfre/Perso/angalsty/homebrew/opt/readline/lib/ -I/sgoinfre/goinfre/Perso/angalsty/homebrew/opt/readline/include -lreadline
all:        $(NAME)
clean:
			$(RM) $(OBJS)
fclean:     clean
			$(RM) $(NAME)
re:         fclean all
.PHONY:     all clean fclean re