#include "../inc/minishell.h"

int	ft_check_error_export(char *argument)
{
	(void)argument;
	//errores para comprobar:
		//primer caracter az_AZ
		//hay un =
		//no hay espacios antes ni después del primer =
	return 0;
}

int	ft_export_without_anything_else(char **envp_copy)
{
	int	i;

	if (envp_copy == NULL)
		return (0);
	i = 0;
	while (envp_copy[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(envp_copy[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	ft_export_builtin(t_command cmd)
{
	int	i;
	//export solo

	if (/* ft_strncmp("export", cmd.comando_a_pelo, ft_strlen("export")) == 0
		&&  */cmd.comando_bonito[1] == NULL)
		return (ft_export_without_anything_else(g_data.envp_copy));
	//ignorar espacios en blanco entre export y varibale=valor -> ya lo hace split
	i = 1;
	while (cmd.comando_bonito[i])
	{
		ft_check_error_export(cmd.comando_bonito[i]);
		i++;
	}

	//bucle para cada argumento de export
	//chequear errores de sintaxis -> escupir error
	//buscar si ya existe
		//si existe reemplazar puntero
		//si no existe
			//preparar matrix con envp_copy len+1
			//copiar todos los punteros
			//añadir nueva linea
			//añadir null final
			
	return (0);
}
