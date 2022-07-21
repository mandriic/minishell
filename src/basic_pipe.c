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
	
	(*cmd1)->comando_a_pelo = ft_strdup("ls");
	(*cmd1)->comando_con_flags = ft_strdup("ls -la");
	(*cmd1)->comando_bonito = ft_split("ls -la", ' ');
	(*cmd1)->infiles = NULL;
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("nl");
	(*cmd2)->comando_con_flags = ft_strdup("nl");
	(*cmd2)->comando_bonito = ft_split("nl", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("wc");
	(*cmd3)->comando_con_flags = ft_strdup("wc -l");
	(*cmd3)->comando_bonito = ft_split("wc -l", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = NULL;
	(*cmd3)->prev = *cmd2;
/* 
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

	(*cmd3)->comando_a_pelo = ft_strdup("wc");
	(*cmd3)->comando_con_flags = ft_strdup("wc -l");
	(*cmd3)->comando_bonito = ft_split("wc -l", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = ft_split("wololo.txt", ' ');
	(*cmd3)->next = NULL;
	(*cmd3)->prev = *cmd2;
 */
}

int	ft_check_infile(t_command *command)
{
	int	fdinfile;

	if (command->infiles != NULL)
	{
		fdinfile = open(*command->infiles, O_RDONLY);
		//if fdinfile < 0 -> gestionar error
		if (dup2(fdinfile, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");//cambiar esto
			exit(EXIT_FAILURE);
		}
		close(fdinfile);
		return (fdinfile);
	}
	else
		return (-1);
}

int	ft_chech_outfile(t_command *command)
{
	int	fdoutfile;

	if (command->outfiles != NULL)
	{
		fdoutfile = open(*command->infiles, O_RDONLY);
		//if fdinfile < 0 -> gestionar error
		if (dup2(fdoutfile, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");//cambiar esto
			exit(EXIT_FAILURE);
		}
		close(fdoutfile);
		return (fdoutfile);
	}
	else
		return (-1);
}

int main(int argc, char *argv[], char *envp[])
{

	//atexit(leaks);
	(void)argc;
	(void)argv;
	int		id;
	int		status;
	// int		fd_in;
	// int		fd_out;

	char	**envp_copy;
	char	*path_to_execve;

(void)id;
(void)path_to_execve;

	t_command	*cmd1 = NULL;
	t_command	*cmd2 = NULL;
	t_command	*cmd3 = NULL;
	t_command	*aux;
	t_command	*aux2;

	envp_copy = ft_copy_enviroment_vars_into_matrix(envp);	
	dar_datos_a_los_cmd(&cmd1, &cmd2, &cmd3);
	aux = cmd1;

	while (aux->next)
	{
		if (pipe(aux->fd))
			perror("pipe");//mejorar esto
		aux = aux->next;
	}
	aux = cmd1;
	while (aux)
	{
		id = fork();
		if (id < 0)
		{
			perror("fork");//mejorar esto
			exit(EXIT_FAILURE);
		}
		if (id == 0)
		{
			path_to_execve = ft_get_path_to_execve(envp_copy, aux->comando_a_pelo);
			if (aux->next != NULL)
			{
				// if (ft_chech_outfile < 0)
				// {
					if (dup2(aux->fd[1], 1) < 0)
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
				// }
			}
			if (aux->prev != NULL)
			{
				// if (ft_check_infile < 0)
				// {
					if (dup2(aux->prev->fd[0], 0) < 0)
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
				// }
			}
			aux2 = cmd1;
			while (aux2->next)
			{
				close(aux2->fd[0]);
				close(aux2->fd[1]);
				aux2 = aux2->next;
			}
			ft_execute(path_to_execve, aux->comando_bonito, envp_copy);
		}
		aux = aux->next;
	}
	aux = cmd1;
	while (aux->next)
	{
		close(aux->fd[0]);
		close(aux->fd[1]);
		aux = aux->next;
	}
	aux = cmd1;
	wait(&status);
	wait(&status);
	wait(&status);
	// while (aux)
	// {
	// 	wait(NULL);
	// 	aux = aux->next;
	// }
	
	
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
