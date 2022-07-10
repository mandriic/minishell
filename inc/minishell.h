#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>	
#include <dirent.h>
#include <signal.h>

typedef struct s_data
{
	char	**cmd_splited; //data->cmd_splited[0] [1] - args
	char 	*cmd_arg_full;
	char	**arg_splited;
	char	*command;
	char	*arg;
	int		menos;
	int		menos_dob;
	int		mas;
	int		mas_dob;
	char 	*sub_arg;
	t_list	*prev;
}t_data;

typedef struct s_vars
{
	t_list	*list;
	char	**split;
	char	*quotes;
	char	*line;
	int		*type;
	
	size_t 	num_pipes;
	size_t	line_len;


}t_vars;
char	*leelinea(void);