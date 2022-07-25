#include "../inc/minishell.h"

int	ft_count_cmd(t_command *cmd)
{
	t_command	*aux;
	int			i;

	if (cmd == NULL)
		return (0);
	i = 0;
	aux = cmd;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	ft_initialize_data()
{
	g_data.num_cmds = 0;
	g_data.num_pipes = 0;
	g_data.last_code = 0;
	g_data.cmd_list = dar_datos_a_los_cmd();
	// inicializado en harcoded.c
	g_data.envp_copy = NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	// atexit(leaks);


	ft_preliminar_check(argc, argv);
	ft_initialize_data();
	g_data.envp_copy = ft_copy_enviroment_vars_into_matrix(envp);//comprobar malloc, no se pensó para ser una variable global
	g_data.num_cmds = ft_count_cmd(g_data.cmd_list);
	ft_putnbr_fd(g_data.num_cmds, 2);
	ft_putstr_fd("\n", 2);
	if (g_data.num_cmds > 1)
		ft_multiple_pipes();

	
	/* Esto crea los pipes y los hijos, en los hijos hace las redirecciones necesarias
	cierra los extremos de los pipes y ejecuta los comandos
	No hay gestión de errores
	No hay gestión de << ni >>, solo < y >
	No hay control de buildins
	 */
	
	return (0);
}

