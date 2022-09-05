#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>	
#include <dirent.h>
#include <signal.h>

typedef struct s_data
{
	int					num_cmds;
	int					num_pipes;
	int					last_code;
	struct s_command	*cmd_list;
	char				**envp_copy;
	char				**export;
}	t_data;

typedef struct s_command
{
	char	**cmd_splited; //data->cmd_splited[0] [1] - args
	char 	*comando_con_flags;
	char	**comando_bonito;
	char	*comando_a_pelo;
	char	*arg;
	int		menos;
	int		menos_dob;
	int		mas;
	int		mas_dob;
	char 	*sub_arg;
	t_list	*prev;
}t_command;

typedef struct s_vars
{
	t_list	*list;
	char	**split;
	char	*quotes;
	char	*line;
	int		*type;
	char	*env_var;
	
	size_t 	num_pipes;
	size_t	line_len;


}t_vars;
void ft_test(t_vars *vars);
char	*leelinea(void);