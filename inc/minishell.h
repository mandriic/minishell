/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:16:58 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/27 20:00:59 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/ioctl.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# define BUFFER_SIZE 10000
# define READ_END    0    /* index pipe extremo lectura */
# define WRITE_END   1 

extern int	g_e_status;

typedef struct s_command
{
	char				**cmd_splited;
	char				**cmd;
	char				*comando_a_pelo;
	char				*vars_resolv;
	char				**pre_comand_bon;
	char				*str_raw;
	char				**pre_args;

	int					pid;
	int					fd[2];
	int					mem_pipe;
	char				*arg;
	char				**infiles;
	char				**heredocs;
	char				**outfiles;
	char				**appends;
	int					menos;
	int					menos_dob;
	int					mas;
	int					mas_dob;
	char				**cpy_env;
	char				*sub_arg;
	struct s_command	*next;
	struct s_command	*prev;
}t_command;

typedef struct s_vars
{
	struct s_command	*cmd_list;
	char				**split;
	char				*quotes;
	char				*line;
	int					*type;
	char				**env_var;
	char				**temp_env;
	char				lastchar;
	int					com_it;
	int					i;
	int					i2;
	int					error;
	char				*temp;
	char				*temp2;
	int					start;
	int					start2;
	char				*var;
	int					need_cleaning;
	int					num_cmds;
	int					last_code;
	char				**export;
	size_t				num_pipes;
	size_t				line_len;
}	t_vars;

int			ft_dup_file(t_command *cmd, t_vars *vars);
char		*ft_last_redir(char **redirs, int outfile);
int			ft_redirections(t_command *cmd, t_vars *vars);
void		c(char *str);
char		*ft_strjoin_mod(char *s1, char *s2);
char		*ft_acumulate(char *dest, char *part);
void		ft_print_arrint(int *arr, char *name);
void		ft_print_dp(char **str, char *name);
char		*leelinea(void);
char		*ft_find_in_env(t_vars *vars, char *to_find);
void		ft_del_from_dob_arr(char *to_del, char ***src);
int			ft_change_temp_env(t_vars *vars, char *name, \
char *new_value, int len);

void		leaks(void);
int			ft_echo(t_vars *vars, t_command *cmd);
int			ft_cd(t_vars *vars, t_command *cmd);
int			ft_pwd(t_vars *vars, t_command *cmd);
int			ft_export(t_vars *vars, t_command *cmd);
int			ft_unset(t_vars *vars, t_command *cmd);
int			ft_env(t_vars *vars, t_command *cmd);
int			ft_exit(t_command *cmd);
int			ft_change_env(t_vars *vars, char *name, char *new_value, int len);
char		*ft_get_value(char *str, char **env);

// fn_list.c
char		**ft_pre_com_bon(char *str, t_vars *vars);
void		ft_merge_comando_args(t_command *data);
int			ft_check_redir(char **arr, t_command *data);
void		ft_resolv_com_bon(t_command *data, t_vars *vars);
t_command	*ft_create_data(char *str, t_vars *vars);
void		ft_add2list(t_vars *vars, t_command *data, \
t_command	**prev, t_command **temp);
void		ft_lst_cmd(t_vars *vars);
int			ft_check_apphdoc(char *str, char **com_bon, int *i, int *type);
int			ft_check_inoutfile(char *str, char **com_bon, int *i, int *type);
void		ft_check_total(char *str, char **com_bon, int *i, int *type);
t_command	*ft_create_data(char *str, t_vars *vars);

// fn_main_readline.c
void		ft_readline(t_vars *vars);
void		ft_submain(t_vars *vars);
char		*ft_cleaning(char *str, t_vars *vars);
int			ft_pre_check(t_vars *vars);
void		ft_end_of_cicle(t_vars *vars);
void		ft_line_exist(t_vars *vars);
void		ft_mi_exec(t_vars *vars);

// fn_mask.c
int			*ft_mask(char *line, t_vars *vars, int check);
char		*ft_acumulate(char *dest, char *part);
int			ft_singquot(char *line, int *type, t_vars *vars, int check);
int			ft_dobquot(char *line, int *type, t_vars *vars, int check);
int			ft_search_redir(char *line, t_vars *vars, int check, int *type);

// fn_pip_splt_trim.c
int			ft_lastpipe(char *str);
char		**spliting(char *wololoco, int *type, \
						size_t num_pipes, t_vars *vars);
void		ft_triming(char **separ, size_t num_pipes, \
						t_vars *vars, int one_comand);
size_t		ft_numpipes(char *wololoco, int *type);
void		ft_subtrim(char **separ, char **temp, int *i, t_vars *vars);

//	fn_pars.c
void		ft_subpars(char *str, t_command *data, t_vars *vars);
void		fr_subargs(char *str, char *temp, t_command *data, t_vars *vars);

//	fn_vars.c
char		*ft_checkif_var(char *str, t_vars *vars);
void		ft_checkif_var_subfoo(char *str, char **acum, \
								int *type, t_vars *vars);
char		*ft_get_env(char *str, int len, t_vars *vars);
void		ft_pre_getenv(char *str, char **acum, t_vars *vars);
void		ft_get_env2(char ***arr, t_vars *vars);
void		ft_sub_get_env(char *str, char *var, int len, int *i);

// fnadd_free.c
void		ft_my_free_d(char **arr);
void		ft_my_free(char *str);
void		ft_free_dob_arr(char **arr);
void		ft_del_list(t_command *list);
void		ft_clean_dp(char **arr, t_vars *vars);

// fn_additional.c
char		**ft_dup_dp(char **src);
int			ft_pre_check(t_vars *vars);
void		ft_end_of_cicle(t_vars *vars);
void		ft_initint(int *i, int len);
void		ft_print_dp(char **str, char *name);
char		**ft_dupl_dp(char **src);
char		*ft_find_in_temp_env(t_vars *vars, char *to_append);
char		**ft_append_to_temp_env(t_vars *vars, char *to_append);
char		**ft_append_to_env(t_vars *vars, char *to_append);
//fnadd_lstmod.c
t_command	*ft_lstnew_mod(t_command *content);
t_command	*ft_lstlast_mod(t_command *lst);
void		ft_lstadd_back_mod(t_command **lst, t_command *new);

//fn_redirs.c
void		ft_heredoc(char **arr, t_command *data, int *i);
void		ft_infile(char **arr, t_command *data, int *i);
void		ft_appends(char **arr, t_command *data, int *i);
void		ft_outfiles(char **arr, t_command *data, int *i);
void		ft_check_redir_create(char **arr, t_command *data, int *i);

void		set_signal(void);
void		handle_process_on(int sig);
void		handle_ctrl_c(int sig);
void		handler_ctrl_d(int signum);
void		set_signal(void);
void		handle_process_on(int sig);
void		handle_ctrl_c(int sig);
void		handler_ctrl_d(int signum);

int			ft_check_if_builtins(t_vars *vars, t_command *cmd);
int			ft_check_if_builtins_true(t_vars *vars, t_command *cmd);

//utils
__int128_t	ft_atoll(const char *str);
int			ft_doublen(char **str);
void		ft_singint_hand(int sigs);
void		ft_here_signal(int sig);
char		*get_next_line(int fd);
void		ft_exit_mini(t_vars *vars);
int			ft_export_err_equal(char *cmd);
void		ft_put_err(char *str, char **temp2);
int			ft_export_err(char *cmd);

#endif
