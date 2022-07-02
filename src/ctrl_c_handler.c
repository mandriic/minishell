#include "../inc/minishell.h"

void leakss()
{
	system("leaks minishell");
}

void	ft_prompt(void)
{
	char *input;
	while (1)
	{
		input = leelinea();
		if (!ft_strncmp ("exit", input, ft_strlen(input)))
		{
			write(1, "exit\n", 5);
			exit (0);
		}
		free (input);
	}
}

void	ft_ctrl_c_handler(int signal)
{
	(void)signal;
	// implementar para cuando se  esté en un proceso hijo 
	// que se quiera detener
	write(1, "\r\n", 2);
	ft_prompt();
	
	return ;
}

void	ft_define_sigaction(struct sigaction *sa)
{
	sa->sa_handler = &ft_ctrl_c_handler;
	sigaction(SIGINT, sa, NULL);
}

int	main()
{
// atexit(leakss)

	struct sigaction	sa;

	ft_define_sigaction(&sa);
	ft_prompt();
	

	return (0);
}