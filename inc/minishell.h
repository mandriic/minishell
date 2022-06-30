#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>	
#include <dirent.h>
#include <signal.h>

typedef struct s_data
{
	char 	*cmd_arg;
	t_list	*prev;
}t_data;

typedef struct s_vars
{
	char	**split;
	char	*quotes;
	char	*line;
	int		*type;
	
	size_t 	num_pipes;
	size_t	line_len;


}t_vars;
char	*leelinea(void);