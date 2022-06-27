#include "../inc/minishell.h"
char **spliting(char *wololoco, int *type)
{
	int i = -1;
	int i2 = 0;
	int num_pipes = 0;
	char **separ;
	int start = 0;
	while(wololoco[++i])
	{
		if (type[i] == 3)
			num_pipes++;
	}
	// if (num_pipes == 0)
	// 	return(&wololoco);
	separ = malloc(sizeof(char *) * num_pipes + 2);
	i = 1;
	while(wololoco[i - 1] != '\0')
	{
		if (type[i - 1] == 3)
		{
			separ[i2++] = ft_substr(wololoco, start, i - start - 1);
			start = i;
			// printf("%d\n", i);
		printf("%s\n", separ[i2 - 1]);

		}
		i++;
	}
	separ[i2++] = ft_substr(wololoco, start, i  - start);
	printf("%s\n", separ[i2 - 1]);

	separ[i2] = NULL;
 	return(separ);
}
int main(void)
{
	char	*wololo;
	char	*wololo_cop;
	size_t		 line_len;
	int i;
	int *type;
	char *cuotes;
	char *finline;
	char d_cuotes;
	char **split;

	cuotes  = "'";
	d_cuotes = '"';
	char *pipe;
	pipe = "|";
	int i_cuot;
	i_cuot = 0;
	while (1)
	{
		wololo = readline(">> ");
		 add_history(wololo);
		 wololo_cop = ft_strdup(wololo);
		line_len = ft_strlen(wololo);
		// printf("%zu\n", line_len	);
		type = malloc(sizeof(int) * line_len);
		i = -1;
		while (wololo[++i] != '\0')
		{
			if(wololo[i] == cuotes[0])
			{
				i_cuot = i_cuot + 2;
				type[i] = 1;
				while (wololo[++i] != cuotes[0])
					type[i] = 0;
				type[i] = 1;
			}
			else if (wololo[i] == d_cuotes)
			{
				i_cuot = i_cuot + 2;
				type[i] = 2;
				while (wololo[++i] != d_cuotes)
					type[i] = 0;
				type[i] = 2;
			}
			else if (wololo[i] == pipe[0] && wololo[i + 1] != '\0')
				type[i] = 3;
			else if (wololo[i] == pipe[0] && wololo[i + 1] == '\0')
				type[i] = 4;
			else
				type[i] = 0;
		}

		split = spliting(wololo_cop, type);
		// i = -1;
			// printf("%s\n", split[0]);

		// while (split[++i])
		// 	printf("%s\n", split[i]);
		i = 0;
		finline = malloc(sizeof(char) * line_len + 1);
		int i2 = 0;
		while (wololo[i])
		{
			if (type[i] == 1 || type[i] == 2)
			{
				i++;
				continue ;
			}
			finline[i2] = wololo[i];
			i++;
			i2++;
		}
		finline[i2] = '\0';
		// printf("%s\n", finline);
		 // printf("%s\n", wololo_cop);
		// for(i = 0; i < line_len; i++)
		// 	printf("%d\n", type[i]);
		i = -1;
		// while (split[++i] != NULL)
		// 	free(split[i]);
		// free(split);
	}

		return (0);
}