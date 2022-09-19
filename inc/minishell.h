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
	int		i;
	int		i2;
	char	*temp;
	int		start;
	int		start2;
	char	*var;
	int		need_cleaning;
	
	size_t 	num_pipes;
	size_t	line_len;


}t_vars;

// fn_lists.c
void		ft_del_list(t_list *list);
t_command	*ft_create_data(char *str, t_list *prev, t_vars *vars);
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


