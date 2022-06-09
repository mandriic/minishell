### --- COLORS --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033;37m'
BLUE	= '\033[1;34m'


### --- VARIABLES --- ###
NAME = minishell


SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/
LIBFT_PATH = libft/
LIB_FT = -I$(LIBFT_PATH) -L$(LIBFT_PATH) -lft

LIB_COMPIL = $(LIB_FT) #añadir ruta brew info readline -lreadline

SRCS = readline_pruebas.c

OBJS = $(SRCS:%.c=bin/%.o)

CC = gcc
CFLAGS =-Wall -Werror -Wextra -g -O0
RM = rm -f

###		RULES		###

all: $(NAME)

bin/%.o: src/%.c
	@mkdir -p $(BIN_PATH)
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@echo $(PURPLE)"[Creating libft]"$(BLUE)
	@$(MAKE) -C $(LIBFT_PATH) --silent
	@echo $(PURPLE)"[Creating fdf]"$(BLUE)
	@$(CC) -o $(NAME) $(OBJS) $(LIB_COMPIL) #-fsanitize=address
	@echo $(GREEN)"$(NAME): ready to be executed"$(WHITE)

clean:
	@$(RM) $(OBJS)
	@rm -rf bin/
	@$(MAKE) -C $(LIBFT_PATH) clean --silent
	@echo $(RED)"[Object Files Deleted]"$(WHITE)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --silent
	@echo $(RED)"[Executable File Deleted]"$(WHITE)

re: fclean 
	@$(MAKE)

.PHONY: all clean fclean re
