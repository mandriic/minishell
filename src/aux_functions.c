# include "../inc/minishell.h"

void	ft_error_exit(char *err_msg)
{
	printf("%s\n", err_msg);
	perror("");
	exit(EXIT_FAILURE);
}

void leaks ()
{
	system ("leaks -fullContent --list minishell");
}

void	ft_free_nodes(t_command *cmd)
{
	t_command	*aux;

	aux = cmd;
	while (aux)
	{
		free(aux->comando_a_pelo);
		free(aux->comando_con_flags);
		ft_free_array(aux->comando_bonito);
		ft_free_array(aux->infiles);
		ft_free_array(aux->outfiles);
		aux = aux->next;
	}
}