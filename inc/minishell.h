#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>	
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>//para linux funcion wait

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
	t_list	*list;//content y next
	char	**split;
	char	*quotes;
	char	*line;
	int		*type;
	char	*env_var;
	
	size_t 	num_pipes;
	size_t	line_len;
}t_vars;

typedef struct s_command
{
	char		*comando_a_pelo;
	char		*comando_con_flags;
	char		**comando_bonito;
	char		**infiles;
	char		**outfiles;
	int			fd[2];
	t_command	*next;
	t_command	*prev;
}t_command;


char	*leelinea(void);
void    ft_cd(char *route);

/* pwd.c */

char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[]);
void	ft_free_array(char **envp_copy);
void	ft_free_list(t_list *lst);
t_list	**ft_copy_enviroment_vars_into_list(t_list **env_copy, char **envp);
void	ft_print_list(t_list *env_copy);
void	ft_pwd(char **env);
void	ft_pwd_2(void);

/* execve.c */
char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[]);
char	*ft_get_path_to_execve(char **envp, char *arg);
void	ft_execute(char *path_to_execve, char **args, char **envp_copy);


