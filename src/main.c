#include "../inc/minishell.h"


int main(int argc, char *argv[], char *envp[])
{

	// atexit(leaks);
	(void)argc;
	(void)argv;
	int		id;
	int		status;
	// int		fd_in;
	// int		fd_out;

	char	**envp_copy;
	char	*path_to_execve;

	t_command	*cmd1 = NULL;
	t_command	*cmd2 = NULL;
	t_command	*cmd3 = NULL;
	// t_command	*cmd4 = NULL;
	t_command	*aux;

	envp_copy = ft_copy_enviroment_vars_into_matrix(envp);	
	dar_datos_a_los_cmd(&cmd1, &cmd2, &cmd3);
	aux = cmd1;

	/* Esto crea los pipes y los hijos, en los hijos hace las redirecciones necesarias
	cierra los extremos de los pipes y ejecuta los comandos
	No hay gestión de errores
	No hay gestión de << ni >>, solo < y >
	No hay control de buildins
	 */
	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = cmd1;
	while (aux)
	{
		path_to_execve = ft_get_path_to_execve(envp_copy, aux->comando_a_pelo);
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
			ft_execute(path_to_execve, aux->comando_bonito, envp_copy);
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
	ft_free_array(envp_copy);
	ft_free_nodes(cmd1);
	aux = cmd1;

	free(cmd1);
	free(cmd2);
	free(cmd3);
	// free(cmd4);
	return (0);
}

