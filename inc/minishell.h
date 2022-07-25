#ifndef MINISHELL_H
# define MINISHELL_H

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
#include <string.h>

typedef struct s_data
{
	int					num_cmds;
	int					num_pipes;
	int					last_code;
	struct s_command	*cmd_list;
	char				**envp_copy;

}	t_data;

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
}	t_vars;

typedef struct s_command
{
	char		*comando_a_pelo;
	char		*comando_con_flags;
	char		**comando_bonito;
	char		**infiles;
	char		**outfiles;
	int			fd[2];
	struct s_command	*next;
	struct s_command	*prev;
	
}	t_command;

t_data	g_data;

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

/* hardcoded.c */
t_command	*dar_datos_a_los_cmd();

/* aux_functions.c */
void	ft_error_exit(char *err_msg);
void	ft_free_nodes(t_command *cmd);
void	ft_preliminar_check(int argc, char *argv[]);

void leaks ();

/* pipe.c */
void	ft_close_pipes(t_command *cmd);
void	ft_dup_infile(t_command *cmd);
void	ft_dup_outfile(t_command *cmd);
void	ft_redirections(t_command *cmd);

/* multiple_pipes */
void	ft_multiple_pipes(void);

#endif