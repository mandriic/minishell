#include "../inc/minishell.h"

// t_data	g_data;

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
// void	ft_initialize_global_var(char **envp)
// {
// 	g_data.cmd_list = dar_datos_a_los_cmd();
// 	g_data.envp_copy = ft_copy_enviroment_vars_into_matrix(envp);
// 	g_data.export = ft_copy_enviroment_vars_into_matrix(envp);
// 	g_data.num_cmds = ft_count_cmd(g_data.cmd_list);
// 	g_data.num_pipes = 0;
// 	g_data.last_code = 0;
// }

int main(int argc, char *argv[], char *envp[])
{
	// atexit(leaks);

	t_vars  vars;

	// ft_preliminar_check(argc, argv);
	vars = (t_vars){};
	vars.split = NULL;
	vars.cmd_list = NULL;
	vars.line = NULL;
	vars.quotes  = "'";

	vars.env_var = ft_dupl_dp(envp);

	ft_readline(&vars);
}

// int	ft_jose(t_vars *vars)
// {
// 	ft_initialize_global_var(vars->env_var);
// 	if (g_data.num_cmds > 1)
// 		ft_multiple_pipes();
// 	else
// 		{
// 			if (ft_is_builtin(*g_data.cmd_list) == true)
// 				{
// 					ft_execute_buitlin(*g_data.cmd_list);
// 				}
// 		}
// 	return (0);
// }
	
	/* Esto crea los pipes y los hijos, en los hijos hace las redirecciones necesarias
	cierra los extremos de los pipes y ejecuta los comandos
	No hay gestión de errores
	No hay gestión de << ni >>, solo < y >
	No hay control de buildins
	 */
	

// }



// void ft_print_arrint(int *arr, char *name)
// {
// 	int i;
// 	int len;
// 	i = 0;
// 	len = sizeof(arr) / sizeof(int);
// 	printf("len%ld\n", sizeof(*arr));
// 	printf("printing array int %s\n{\n", name);
// 	while (i != len)
// 	{
// 		printf("\t %s[%d] = %d\n" , name, i, arr[5]);
// 		i++;
// 	}
// 	printf("{\n");
// }
