# include "../inc/minishell.h"

int	ft_child(int *fd)
{
	int x;

	close(fd[0]);
	x = 10;
	if (write(fd[1], &x, sizeof(int)) == -1)
	{
		printf("Error writing to the pipe\n");
		return (1);
	}
	close(fd[1]);
	return (x);
}

int	ft_parent(int *fd)
{
	int y;

	close (fd[1]);
	if (read(fd[0], &y, sizeof(int)) == -1)
	{
		printf("Error reading from the pipe\n");
		return (1);
	}
	close (fd[0]);
	return (y);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *cmd1[] = {
		"ls",
		"-la",
		"/Users/JoseGF/Desktop",
		NULL
	};
	char *cmd2[] = {
		"grep",
		"txt",
		NULL
	};
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


	return (0);
}
