#include "../inc/minishell.h"
size_t ft_numpipes(char *wololoco, int *type)
{
	int num_pipes;
	int	i;

	i = -1;
	num_pipes = 0;
	while(wololoco[++i])
	{
		if (type[i] == 3)
			num_pipes++;
	}
	return (num_pipes);
}
char **spliting(char *wololoco, int *type, size_t num_pipes)
{
	int i = -1;
	int i2 = 0;
	char **separ;
	int start = 0;
	
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
			else if (wololo[i] == '"')
			{
				i_cuot = i_cuot + 2;
				type[i] = 2;
				while (wololo[++i] != d_cuotes)
					type[i] = 0;
				type[i] = 2;
			}
			else if (wololo[i] == '|' && wololo[i + 1] != '\0')
				type[i] = 3;
			else if (wololo[i] == '|' && wololo[i + 1] == '\0')
				type[i] = 4;
			else
				type[i] = 0;
		}
		size_t num_pipes = 0;
		num_pipes = ft_numpipes(wololo_cop, type);
		if (num_pipes)
			split = spliting(wololo_cop, type, num_pipes);
		else
		{
			split = malloc(sizeof(char *) * 2);
			split[0] = wololo_cop;
		}
		printf("%s\n", split[0]);
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