


R42LFLAG = -L/Users/$USER/.brew/opt/readline/lib
R42IFLAG = -I/Users/$USER/.brew/opt/readline/include
R42LFLAGM = -L/opt/homebrew/opt/readline/lib 
R42IFLAGM = -I/opt/homebrew/opt/readline/include
R42LFLAGU = -L/usr/share/readline 
R42IFLAGU = -I/usr/include/readline
INCS     = inc/
BIN_PATH = bin/
SRCS_PATH = src/
LIBFT_PATH = libft/
LIBFT_FLAGS = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft
SRCS = fn_list.c fn_main_readline.c fnadd_free.c fnadd_libftmod.c fn_additional.c fn_cleaning.c fn_getenvs.c \
fn_mask.c fn_pip_splt_trim.c fn_vars.c main.c fn_redirs.c fn_create_data.c signal.c fn_addit_4env.c ft_atoll.c \
ft_export.c ft_cd.c ft_unset.c ft_exit.c ft_pwd.c ft_echo.c ft_env.c get_next_line.c fn_add_doubl_arr.c fn_addit_4loc_env.c \
fn_execute_0.c fn_execute_1.c fn_execute_2.c fn_execute_3.c fn_execute_4.c fn_execute_5.c ft_export_1.c

CC       = gcc

OBJS     = $(SRCS:%.c=$(BIN_PATH)%.o)

CFLAGS   = -g -O0 #-Wall -Wextra -Werror

NAME     = minishell

RM       = rm -f

$(BIN_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS) $(R42IFLAGM) #-I/opt/homebrew/opt/readline/include

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -I$(INCS) -o $(NAME) $(R42LFLAGM) $(R42IFLAGM) -lreadline #-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C $(LIBFT_PATH)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
