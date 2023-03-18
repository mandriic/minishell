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
	vars.env_var = envp;
	ft_readline(&vars);
}
