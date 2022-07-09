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
int main(int argc, char *argv[], char *envp[])
{
	atexit(leaks);
	(void)argc;
	(void)argv;

	char *cmd1[] = {
		"ls",
		"-la",
		"/Users/JoseGF/Desktop",
		NULL
	};
	char *cmd2[] = {
		"wc",
		NULL
	};
	char	outfile[] = "wololo.txt";

	char **envp_copy;
	char	*path_to_execve;

	envp_copy = ft_copy_enviroment_vars_into_matrix(envp);
	path_to_execve = ft_get_path_to_execve(envp_copy, cmd1[0]);

	int	id;
	int	id2;
	int	fd1[2]; //0 leer, 1 escribir
	int	fd2;

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
			write(1, "XXXX\n", 5);
			close(fd2);
			//end if
			ft_execute(path_to_execve, cmd2, envp_copy);
			// if (execve("/usr/bin/wc", cmd2, envp) == -1)
			// 	write(2, "Oh oh\n", 6);
		}
		else
		{
			close(fd1[0]);
		}
		wait(NULL);
		wait(NULL);

	}



	return (0);
}

/* 
(void)cmd1;
(void)cmd2;

	int	 fd[2];
	int	 id;
	int		z;

	if (pipe(fd) == -1)
	{
		printf("Error abriendo el pipe\n");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		printf("Error forking\n");
		return (-1);
	}
	if (id == 0)
	{
		ft_child(fd);
	}
	else
	{
		z = ft_parent(fd);
		if (z == 1)
		{
			printf("Check errors please\n");
			return (2);
		}
		else
		{
			printf("10 x 2 es %d\n", z * 2);
		}
		return (0);
	}
 */