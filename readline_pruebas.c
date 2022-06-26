#include "../inc/minishell.h"

int main(void)
{
	char	*wololo;
	size_t		 line_len;
	int i;
	int *type;
	char *cuotes;
	char *finline;
	char d_cuotes;
	// char *split[100];

	cuotes  = "'";
	d_cuotes = '"';
	char *pipe;
	pipe = "|";
	int i_cuot;
	i_cuot = 0;
	// int  i_sub = 0;
	// int start = 0;
	while (1)
	{
		wololo = readline(">> ");
		 add_history(wololo);
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
			// else if (wololo[i] == pipe[0])
			// {
			// 	type[i] = 3;
			// }

			else
				type[i] = 0;
			 // printf("%d", type[i]);
		}
		i = 0;
		finline = malloc(sizeof(char) * line_len + 1);
		// finline[line_len - i_cuot + 1] = '\0';
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
		// while(split[++i])
			// printf("%c\n", split[i][0]);
		printf("%s\n", finline);
	}
		// i = -1;
		// while (wololo[++i])
		// {
		// 	if (wololo[i] == cuotes[0])
		// 	{
		// 		while (wololo[i] != cuotes[0])
		// 		{
		// 			type[i++] = 0;
		// 		}
		// 	}
		// 	if (wololo[i] == d_cuotes)
		// 	{
		// 		while(wololo[i] != d_cuotes)
		// 		{
		// 			type[i++] = 0;
		// 		}
		// 	}
		// }
		i = -1;
		while (++i != (int)line_len)
			printf("%d", type[i]);
		// i= -1;
		// // write(1, "\n", 1);
		// while (wololo[++i])
		// 	printf("%c", wololo[i]);


		return (0);
}