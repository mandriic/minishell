#include "../inc/minishell.h"


int	main()
{
	char *line;
	char *env;
	DIR *dir;
	struct dirent *dirent;
	while (1)
	{
        line = readline ("Minishell>");
		add_history(line);
		dir = opendir("/home/nico/");
		dirent = readdir(dir);
		printf("%c\n", dirent->d_name[1]);
		printf("%d\n", dirent->d_type);
		printf("%ld\n", dirent->d_ino);
		// if (line != NULL)
		// {
		// 	env = getenv(line);
		// 	printf("%s\n", env);
		// }
        // printf("es0 hay que parsear ->(%s) \n", line);

		free(line);
	}
	return (0);
}
