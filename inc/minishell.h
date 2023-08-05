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
# include <sys/types.h>
# include <dirent.h>
# define BUFFER_SIZE 10000
# define READ_END    0    /* index pipe extremo lectura */
# define WRITE_END   1 

// typedef struct s_data
// {
// 	int					num_cmds;
// 	int					num_pipes;
// 	int					last_code;
// 	struct s_command	*cmd_list;
// 	char				**envp_copy;
// 	char				**export;
// }	t_data;

//structuras estan violadas por todo el mundo, las voy a limpiar en el futuro 
typedef struct s_command //structura de UN comando. Si existe un pipe, se crea una nueva structura t_command
{
	char	**cmd_splited; //data->cmd_splited[0] [1] - args
	// char 	*comando_con_flags;//este se transforma en cmd con un split
	char	**cmd; //array de strings, cada string es comando[0] y comando[1] son los args o flags etc. comando[x] es NULL
	char	*comando_a_pelo; // es un artifacto de la funcion ft_pre_com_bon, se puede borrar creo, pero no estoy seguro
	char	*vars_resolv; //es un artifacto de la funcion ft_pre_com_bon, se puede borrar creo, pero no estoy seguro
	char	**pre_comand_bon; //utiliza en parser, variable tecnica
	char	**pre_args; //utiliza en parser, variable tecnica
	//pid_t*	child_pid;
	int 	pid; //pid del proceso (no se si esta realizado)
	int		fd[2]; //pipe 
	int		mem_pipe; // ni idea
	char	*arg; // ni idea
	char	**infiles;  // 	< redirecciones cada string de este array es texto que va despues de <
	char	**heredocs; //	<< redirecciones cada string de este array es texto que va despues de <<
	char	**outfiles; //	> redirecciones cada string de este array es texto que va despues de >
	char	**appends; 	//	>> 
	int		menos; // artificato de la funcion ft_check_redir, se puede borrar creo, pero no estoy seguro
	int		menos_dob; // artificato de la funcion ft_check_redir, se puede borrar creo, pero no estoy seguro
	int		mas; // artificato de la funcion ft_check_redir, se puede borrar creo, pero no estoy seguro
	int		mas_dob; // artificato de la funcion ft_check_redir, se puede borrar creo, pero no estoy seguro
	char   **cpy_env; // copia del envp
	char 	*sub_arg; // ni idea, parece a variable tecnica
	struct s_command	*next; //siguiente comando en la lista
	struct s_command	*prev; //comando anterior en la lista
}t_command;

typedef struct s_vars
{
	// t_command	*list;
	struct s_command	*cmd_list; //lista de comandos que contiene todos t_command y cmd_list->next es el siguiente comando
	char	**split; // tecnica variable
	char	*quotes; // tecnica variable
	char	*line; //linea que devuelve readline
	int		*type; // tecnica variable
	char	**env_var; // variable de entorno, que se copia en envp_copy
	char 	**temp_env; //technica variable
	int		i; //technica variable
	int		i2; //technica variable
	char	*temp; //technica variable
	char	*temp2; //technica variable
	int		start; //technica variable
	int		start2; //technica variable
	char	*var; //technica variable
	int		need_cleaning; //technica variable
	int					num_cmds; //numero de comandos
	// int					num_pipes;
	int					last_code; //codigo de salida (no esta realizado)
	// char				**envp_copy;
	// char				**export;  //variable fatal creada porque palabra export es reservada
	
	size_t 	num_pipes; //numero de pipes
	size_t	line_len; //longitud de la linea
}	t_vars;

// typedef struct s_command
// {
// 	char		*comando_a_pelo;
// 	char		*comando_con_flags;
// 	char		**cmd;
// 	char		**infiles;
// 	char		**outfiles;

// 	struct s_command	*next;
// 	struct s_command	*prev;

// }	t_command;

// extern t_data	g_data;
void c(char *str); //funcion de debug

void ft_print_arrint(int *arr, char *name); //funcion de debug
void ft_print_dp(char **str, char *name); //funcion de debug
char	*leelinea(void);  // ni idea
// void	ft_cd(char *route);

//export.c
// void	ft_add_line_to_matrix(char ***matrix, char *line); //pepeline :( )

/* pwd.c */

// char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[]);
// void	ft_free_array(char **envp_copy);
// void	ft_free_list(t_command *lst);
// t_command	**ft_copy_enviroment_vars_into_list(t_command **env_copy, char **envp);
// void	ft_print_command(t_command *env_copy);
// void	ft_pwd(char **env);
// void	ft_pwd_2(void);

/* execve.c */
// char	**ft_copy_enviroment_vars_into_matrix(char *envp_original[]);
// char	*ft_get_path_to_execve(char **envp, char *arg);
// void	ft_execute(char *path_to_execve, char **args, char **envp_copy);  //pepeline :( 

/* hardcoded.c */
// t_command	*dar_datos_a_los_cmd();

/* aux_functions.c */
// void	ft_error_exit(char *err_msg);
// void	ft_free_nodes(t_command *cmd);
// void	ft_preliminar_check(int argc, char *argv[]);
// int		ft_strchr_index(char *str, char c);
// int		ft_env_var_key_len(char *env_var);
// void	ft_print_matrix(char **matrix, int fd);
// int		ft_matrix_len(char **matrix);


void leaks (); //funcion de debug

/* pipe.c */
// void	ft_close_pipes(t_command *cmd);
// void	ft_dup_infile(t_command *cmd);
// void	ft_dup_outfile(t_command *cmd);
// void	ft_redirections(t_command *cmd);

/* multiple_pipes */
// void	ft_multiple_pipes(t_vars *vars);

/* builtins.c */
int	ft_echo(t_vars *vars, t_command *cmd); //builtins
int	ft_cd(t_vars *vars, t_command *cmd); //builtins
int	ft_pwd(t_vars *vars, t_command *cmd); //builtins
int		ft_export(t_vars *vars, t_command *cmd); //builtins
int	ft_unset(t_vars *vars, t_command *cmd); //builtins
int	ft_env(t_vars *vars, t_command *cmd); //builtins
int	ft_exit(t_vars *vars, t_command *cmd); //builtins
int	ft_env(t_vars *vars, t_command *cmd);  //builtins 
int	ft_exit(t_vars *vars, t_command *cmd); //builtins
int ft_change_env(t_vars *vars, char *name, char *new_value, int len); //builtins cambiar variable de entorno
char *ft_get_value(char *str, char **env); //builtins obtener valor de variable de entorno
// bool	ft_is_builtin(t_command cmd);
// void	ft_execute_buitlin(t_command cmd, t_vars *vars);

//main.c

// int	ft_jose(t_vars *vars);

/* export.c */
// int	ft_check_existing_variable_in_matrix(char **matrix, char *var_name, int *index);

// fn_list.c parseo todo
char		**ft_pre_com_bon(char *str, t_vars *vars); // funcion de parseo
void		ft_merge_comando_args(t_command *data); // funcion de parseo
int			ft_check_redir(char **arr, t_command *data); // funcion de parseo
void		ft_resolv_com_bon(t_command *data, t_vars *vars); // funcion de parseo
t_command 	*ft_create_data(char *str, t_vars *vars); // funcion de parseo
void		ft_add2list(t_vars *vars, t_command *data, t_command **prev, t_command **temp); // funcion de parseo
void		ft_lst_cmd(t_vars *vars); // funcion de parseo
int			ft_check_apphdoc(char *str, char **com_bon, int *i, int *type);
int			ft_check_inoutfile(char *str, char **com_bon, int *i, int *type);
void		ft_check_total(char *str, char **com_bon, int *i, int *type);
t_command 	*ft_create_data(char *str, t_vars *vars);


// fn_main_readline.c
void		ft_readline(t_vars *vars);
void	    ft_submain(t_vars *vars);
char		*ft_cleaning(char *str, t_vars *vars);
int			ft_pre_check(t_vars *vars);
void    	ft_end_of_cicle(t_vars *vars);
void    	ft_line_exist(t_vars *vars);

// fn_mask.c
int			*ft_mask(char *line, t_vars *vars, int check);
char		*ft_acumulate(char *dest, char *part);
int			ft_singquot(char *line, int *type, t_vars *vars, int check);
int			ft_dobquot(char *line, int *type, t_vars *vars, int check);
int			ft_search_redir(char *line, t_vars *vars, int check, int *type);

// fn_pip_splt_trim.c
int		    ft_lastpipe(char *str);
char		**spliting(char *wololoco, int *type, size_t num_pipes, t_vars *vars);
void    	ft_triming(char **separ, size_t num_pipes, t_vars *vars, int one_comand);
size_t 		ft_numpipes(char *wololoco, int *type);
// void		ft_split_args(t_command *data, t_vars *vars); // <- FUncion comentada, no se usa, se puede usar si va a hacer falta comando bonito
void		ft_subtrim(char **separ, char **temp, int *i, t_vars *vars);

//	fn_pars.c
void		ft_subpars(char *str, t_command *data, t_vars * vars);
void		fr_subargs(char *str, char *temp, t_command *data, t_vars *vars);

//	fn_vars.c
char		*ft_checkif_var(char *str, t_vars *vars);
void		ft_checkif_var_subfoo(char *str, char **acum, int *type, t_vars *vars);
char		*ft_get_env(char *str, int len, t_vars *vars);
void		ft_pre_getenv(char *str, char **acum, t_vars *vars);
void		ft_get_env2(char ***arr, t_vars *vars);
void		ft_sub_get_env(char *str, char *var, int len, int *i);

// fnadd_free.c
void ft_my_free_d(char **arr);
void ft_my_free(char *str);
void ft_free_dob_arr(char **arr);
void	ft_del_list(t_command *list);
void	ft_clean_dp(char **arr, t_vars *vars);

// fn_additional.c
char		**ft_dup_dp(char **src);
int	ft_pre_check(t_vars *vars);
void	ft_end_of_cicle(t_vars *vars);
void	ft_initint(int *i, int len);
void	ft_print_dp(char **str, char *name);
char	**ft_dupl_dp(char **src);
char *ft_find_in_temp_env(t_vars *vars, char *to_append);
char **ft_append_to_temp_env(t_vars *vars, char *to_append);
char **ft_append_to_env(t_vars *vars, char *to_append);
//fnadd_lstmod.c
t_command	*ft_lstnew_mod(t_command *content);
t_command	*ft_lstlast_mod(t_command *lst);
void	ft_lstadd_back_mod(t_command **lst, t_command *new);

//fn_redirs.c
void	ft_heredoc(char **arr, t_command *data, int *i);
void	ft_infile(char **arr, t_command *data, int *i);
void	ft_appends(char **arr, t_command *data, int *i);
void	ft_outfiles(char **arr, t_command *data, int *i);
void	ft_check_redir_create(char **arr, t_command *data, int *i);


//fn_cd.c
void ft_chdir(t_vars *vars);

void ft_mi_exec(t_vars *vars);

int ft_check_if_builtins(t_vars *vars, t_command *cmd);

int ft_check_if_builtins_true(t_vars *vars, t_command *cmd);

int ft_check_if_builtins_true(t_vars *vars, t_command *cmd);
#endif

