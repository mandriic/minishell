#include "../inc/minishell.h"

void	ft_multiple_pipes(t_vars *vars)
{
	t_command	*aux;
	char	*path_to_execve;
	int		id;
	int		status;

	aux = vars->cmd_list;

	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = vars->cmd_list;
	while (aux)
	{
		path_to_execve = ft_get_path_to_execve(vars->env_var, aux->comando_a_pelo);
		id = fork();
		if (id < 0)
		{
			perror("fork");//mejorar esto gestion errores
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			ft_redirections(aux);
			ft_close_pipes(aux);
			ft_execute(path_to_execve, aux->comando_bonito, vars->env_var);
		}
		free(path_to_execve);
		aux = aux->next;
	}
	ft_close_pipes(vars->cmd_list);
	aux = vars->cmd_list;
	while (aux)
	{
		wait(&status);
		ft_putnbr_fd(status, 2);
		ft_putstr_fd("\n", 2);
		aux = aux->next;
	}
	ft_free_array(vars->env_var);
	ft_free_nodes(vars->cmd_list);
}