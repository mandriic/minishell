#include "../inc/minishell.h"

void	ft_multiple_pipes()
{
	t_command	*cmd1 = NULL;
	t_command	*cmd2 = NULL;
	t_command	*cmd3 = NULL;
	// t_command	*cmd4 = NULL;
	t_command	*aux;

	char	*path_to_execve;
	int		id;
	int		status;

	dar_datos_a_los_cmd();
	aux = cmd1;

	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = cmd1;
	while (aux)
	{
		path_to_execve = ft_get_path_to_execve(g_data.envp_copy, aux->comando_a_pelo);
		id = fork();
		if (id < 0)
		{
			perror("fork");//mejorar esto
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			ft_redirections(aux);
			ft_close_pipes(cmd1);
			ft_execute(path_to_execve, aux->comando_bonito, g_data.envp_copy);
		}
		free(path_to_execve);
		aux = aux->next;
	}
	ft_close_pipes(cmd1);
	aux = cmd1;
	while (aux)
	{
		wait(&status);
		ft_putnbr_fd(status, 2);
		ft_putstr_fd("\n", 2);
		aux = aux->next;
	}
	ft_free_array(g_data.envp_copy);
	ft_free_nodes(cmd1);
	aux = cmd1;

	free(cmd1);
	free(cmd2);
	free(cmd3);
	// free(cmd4);
}