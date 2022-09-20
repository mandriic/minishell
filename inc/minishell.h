#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>	
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>//para linux funcion wait
# include <sys/param.h>
# include <string.h>

//no hay nada preparado para $_ (el último comando utilizado, se guarda en las variables de entorno)

// typedef struct s_data
// {
// 	int					num_cmds;
// 	int					num_pipes;
// 	int					last_code;
// 	struct s_command	*cmd_list;
// 	char				**envp_copy;
// 	char				**export;
// }	t_data;

typedef struct s_command
{
	char	**cmd_splited; //data->cmd_splited[0] [1] - args
	char 	*comando_con_flags;
	char	**comando_bonito;//este si se usa
	char	*comando_a_pelo;//este si se usa
	int		fd[2];
	char	*arg;
	int		menos;
	int		menos_dob;
	int		mas;
	int		mas_dob;
	char 	*sub_arg;
	t_list	*next;
}t_command;

typedef struct s_vars
{
	t_list	*list;
	struct s_command	*cmd_list; //t_comad
	char	**split;
	char	*quotes;
	char	*line;
	int		*type;
	char	**env_var;
	int		i;
	int		i2;
	char	*temp;
	char	*temp2;
	int		start;
	int		start2;
	char	*var;
	int		need_cleaning;
	int					num_cmds;
	// int					num_pipes;
	int					last_code;
	// char				**envp_copy;
	char				**export;
	
	size_t 	num_pipes;
	size_t	line_len;
}	t_vars;

// typedef struct s_command
// {
// 	char		*comando_a_pelo;
// 	char		*comando_con_flags;
// 	char		**comando_bonito;
// 	char		**infiles;
// 	char		**outfiles;

// 	struct s_command	*next;
// 	struct s_command	*prev;

// }	t_command;

// extern t_data	g_data;

char	*leelinea(void);
void	ft_cd(char *route);

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
int		ft_strchr_index(char *str, char c);
int		ft_env_var_key_len(char *env_var);
void	ft_print_matrix(char **matrix, int fd);
int		ft_matrix_len(char **matrix);


void leaks ();

/* pipe.c */
void	ft_close_pipes(t_command *cmd);
void	ft_dup_infile(t_command *cmd);
void	ft_dup_outfile(t_command *cmd);
void	ft_redirections(t_command *cmd);

/* multiple_pipes */
void	ft_multiple_pipes(t_vars *vars);

/* builtins.c */
void	ft_echo_builtin(t_command cmd);
void	ft_cd_builtin(t_command cmd);
void	ft_pwd_builtin(t_command cmd);
int		ft_export_builtin(t_command cmd);
void	ft_unset_builtin(t_command cmd, t_vars *vars);
void	ft_env_builtin(t_command cmd);
void	ft_exit_builtin(t_command cmd);

bool	ft_is_builtin(t_command cmd);
void	ft_execute_buitlin(t_command cmd);

//main.c

int	ft_jose(t_vars *vars);

/* export.c */
int	ft_check_existing_variable_in_matrix(char **matrix, char *var_name, int *index);

// fn_lists.c
void		ft_del_list(t_list *list);
t_command	*ft_create_data(char *str, t_vars *vars);
void		ft_lst_cmd(t_vars *vars);

// fn_main_readline.c
void		ft_readline(void);
void	    ft_submain(t_vars *vars);
char		*ft_cleaning(char *str, t_vars *vars);
int			ft_pre_check(t_vars *vars);
void    	ft_end_of_cicle(t_vars *vars);
void    	ft_line_exist(t_vars *vars);

// fn_mask.c
int			*ft_mask(char *line, t_vars *vars);
char		*ft_acumulate(char *dest, char *part);
int			ft_singquot(char *line, int *type, t_vars *vars);
int			ft_dobquot(char *line, int *type, t_vars *vars);



// fn_pip_splt_trim.c
int		    ft_lastpipe(char *str);
char		**spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars);
void    	ft_triming(char **separ, size_t num_pipes, t_vars *vars, int one_comand);
size_t 		ft_numpipes(char *wololoco, int *type);
void		ft_split_args(t_command *data, t_vars *vars); // <- FUncion comentada, no se usa, se puede usar si va a hacer falta comando bonito
void		ft_subtrim(char **separ, char **temp, int *i, int *i2, t_vars *vars);



//	fn_pars.c
void		ft_subpars(char *str, t_command *data, t_vars * vars);
void		fr_subargs(char *str, char *temp, t_command *data, t_vars *vars);

//	fn_vars.c
char		*ft_checkif_var(char *str, t_vars *vars);
void		ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars);
char		*ft_get_env(char *str, int len);
void		ft_pre_getenv(char *str, char **acum, t_vars *vars);

#endif
