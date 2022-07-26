#include "../inc/minishell.h"

t_data	g_data;

bool	ft_is_builtin(t_command cmd)//pasar puntero y proteger??
{
	if (ft_strncmp("echo", cmd.comando_a_pelo, ft_strlen("echo") == 0)
		|| ft_strncmp("cd", cmd.comando_a_pelo, ft_strlen("cd") == 0)
		|| ft_strncmp("pwd", cmd.comando_a_pelo, ft_strlen("pwd") == 0)
		|| ft_strncmp("export", cmd.comando_a_pelo, ft_strlen("export") == 0)
		|| ft_strncmp("unset", cmd.comando_a_pelo, ft_strlen("unset") == 0)
		|| ft_strncmp("env", cmd.comando_a_pelo, ft_strlen("env") == 0)
		|| ft_strncmp("exit", cmd.comando_a_pelo, ft_strlen("exit") == 0))
		return (true);

	return (false);
	/* echo, cd, pwd, export, unset, env, exit */
}

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

void	ft_initialize_global_var(char **envp)
{
	g_data.cmd_list = dar_datos_a_los_cmd();
	g_data.envp_copy = ft_copy_enviroment_vars_into_matrix(envp);
	g_data.num_cmds = ft_count_cmd(g_data.cmd_list);
	g_data.num_pipes = 0;
	g_data.last_code = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	// atexit(leaks);

	ft_preliminar_check(argc, argv);
	ft_initialize_global_var(envp);
	printf("%s, %s, %s\n", g_data.cmd_list->comando_a_pelo, g_data.cmd_list->next->comando_a_pelo, g_data.cmd_list->next->next->comando_a_pelo);
	printf("%d, %d, %d\n", ft_is_builtin(*(g_data.cmd_list)),  ft_is_builtin(*(g_data.cmd_list->next)), ft_is_builtin(*(g_data.cmd_list->next->next)));

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

