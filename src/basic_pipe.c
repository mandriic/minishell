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

void	dar_datos_a_los_cmd(t_command **cmd1, t_command **cmd2, t_command **cmd3)
{
	*cmd1 = malloc(sizeof(t_command));
	*cmd2 = malloc(sizeof(t_command));
	*cmd3 = malloc(sizeof(t_command));

	(*cmd1)->comando_a_pelo = ft_strdup("cat");
	(*cmd1)->comando_con_flags = ft_strdup("cat");
	(*cmd1)->comando_bonito = ft_split("cat", ' ');
	(*cmd1)->infiles = ft_split("lotr.txt", ' ');
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("grep");
	(*cmd2)->comando_con_flags = ft_strdup("grep Moria");
	(*cmd2)->comando_bonito = ft_split("grep Moria", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("grep");
	(*cmd3)->comando_con_flags = ft_strdup("grep -n Moria");
	(*cmd3)->comando_bonito = ft_split("grep -n Moria", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = ft_split("mierda.txt", ' ');
	(*cmd3)->next = NULL;
	(*cmd3)->prev = *cmd2;
}

int main(int argc, char *argv[], char *envp[])
{

	atexit(leaks);
	(void)argc;
	(void)argv;
	int		id;
	int		fd_infile;
	int		fd_outfile;
	(void)	fd_infile;
	(void)	fd_outfile;
	// int		number_of_pipes = 3;

	
	// char	infile[] = "lotr.txt";
	// char	outfile[] = "wololo.txt";

	char	**envp_copy;
	char	*path_to_execve;

	t_command *cmd1 = NULL;
	t_command *cmd2 = NULL;
	t_command *cmd3 = NULL;
	t_command *aux;

	(void)cmd1;
	(void)cmd2;
	(void)cmd3;
	// (void)infile;
	// (void)outfile;
	(void)envp_copy;
	(void)path_to_execve;

	envp_copy = ft_copy_enviroment_vars_into_matrix(envp);
	
	dar_datos_a_los_cmd(&cmd1, &cmd2, &cmd3);
	aux = cmd1;
	/*
	<lotr.txt cat | grep Moria | grep -n mine >mierda.txt
	*/
	while (aux)
	{
		pipe(aux->fd);
		id = fork();
		path_to_execve = ft_get_path_to_execve(envp_copy, aux->comando_a_pelo);
		if (id == 0)
		{
			//revisar que haya infile
			//revisar que todos los infile sean accesibles
			//si no hay infile esto no hay que hacerlo
			printf("%s\n", path_to_execve);
			if (access(*aux->infiles, R_OK) != 0)
				exit(EXIT_FAILURE);//mejorar esta salida de error, solo vale para pruebas
			fd_infile = open(*aux->infiles, O_RDONLY);
			dup2(fd_infile, STDIN_FILENO);
			close(fd_infile);
			return (0);
		}
		aux = aux->next;
		wait(NULL);
		free(path_to_execve);
	}
	ft_free_array(envp_copy);
	free(cmd1);
	free(cmd2);
	free(cmd3);
	return (0);
}

/* 
	char *cmd1[] = {
		"ls",
		"-la",
		// "/Users/JoseGF/Desktop",
		// "/home/josgarci/minishell",
		"/Users/josgarci/Desktop",
		NULL
	};
	char *cmd2[] = {
		"wc",
		NULL
	};

	int	id;
	int	id2;
	int	fd1[2]; //0 leer, 1 escribir
	int	fd2;

	path_to_execve = ft_get_path_to_execve(envp_copy, cmd1[0]);

	if (pipe(fd1) == -1)
		ft_error_exit("Error pipe");
	id = fork();
	if (id == -1)
		ft_error_exit("Error fork");
	if (id == 0)
	{

		if (close(fd1[0]) == -1)
			ft_error_exit("Error close");
		if (dup2(fd1[1], STDOUT_FILENO) == -1)
			ft_error_exit("Error dup");
		if (close(fd1[1]) == -1)
			ft_error_exit("Error close");
		ft_execute(path_to_execve, cmd1, envp_copy);
		// if (execve("/bin/ls", cmd1, envp) == -1)
			// ft_error_exit("Error comando ejecución");
	}
	else
	{
		free(path_to_execve);
		close(fd1[1]);
		// close(fd1[0]);
		path_to_execve = ft_get_path_to_execve(envp_copy, cmd2[0]);

		id2 = fork();
		if (id2 == 0)
		{

			//if hay redirección
			fd2 = open(outfile, O_WRONLY | O_CREAT, 0744);
			dup2(fd1[0], STDIN_FILENO);
			close(fd1[0]);
			dup2(fd2, STDOUT_FILENO);
			close(fd2);
			//end if
			ft_execute(path_to_execve, cmd2, envp_copy);
			// if (execve("/usr/bin/wc", cmd2, envp) == -1)
			// 	write(2, "Oh oh\n", 6);
		}
	close(fd1[0]);
	wait(NULL);
	wait(NULL);
	free(path_to_execve);
	ft_free_array(envp_copy);

	}
 */