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

void	ft_initialize_global_var(t_vars *vars)
{
	vars->cmd_list = dar_datos_a_los_cmd();
	vars->env_var = ft_copy_enviroment_vars_into_matrix(vars->env_var);
	vars->export = ft_copy_enviroment_vars_into_matrix(vars->env_var);
	vars->num_cmds = ft_count_cmd(vars->cmd_list);
	vars->num_pipes = 0;
	vars->last_code = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	// atexit(leaks);

	t_vars  vars;

	ft_preliminar_check(argc, argv);
	vars = (t_vars){};
	vars.split = NULL;
	vars.list = NULL;
	vars.line = NULL;
	vars.quotes  = "'";
	vars.env_var = envp;

	ft_readline();
}

int	ft_jose(t_vars *vars)
{
	ft_initialize_global_var(vars);
	if (vars->num_cmds > 1)
		ft_multiple_pipes(vars);
	else
		{
			if (ft_is_builtin(*vars->cmd_list) == true)
				{
					ft_execute_buitlin(*vars->cmd_list);
				}
		}
	return (0);
}
	
	/* Esto crea los pipes y los hijos, en los hijos hace las redirecciones necesarias
	cierra los extremos de los pipes y ejecuta los comandos
	No hay gestión de errores
	No hay gestión de << ni >>, solo < y >
	No hay control de buildins
	 */
	

// }

