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
	separ = malloc(sizeof(char *) * num_pipes +1);
	i = 0;
	while(wololoco[i] != '\0')
	{
		if (type[i] == 3)
		{
			separ[i2++] = ft_substr(wololoco, start, i - 1);
			start = i + 1;
			// write(1, "1",1);
		}
		i++;
	}
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
			else if (wololo[i] == pipe[0])
				type[i] = 3;
			else
				type[i] = 0;
		}
		split = spliting(wololo_cop, type);	
		printf("%s\n", split[1]);
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
	// 	for(i = 0; i < line_len; i++)
	// 		printf("%d\n", type[i]);
	}

		return (0);
}