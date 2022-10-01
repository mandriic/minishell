#include "../inc/minishell.h"

// t_data	g_data;

int	ft_count_cmd(t_command *cmd)
{
	t_command	*aux;
	int			i;

	if (cmd == NULL)
		return (0);
	i = 0;
	aux = cmd;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

// void ft_print_dp(char **str, char *name)
// {
// 	int i; 

// 	i = -1;
// 	printf("_____________printing doble punbtero %s _______\n", name);
// 	while (str[++i])
// 	{
// 		printf("\t %s[%d] = .%s.\n" , name, i, str[i]);
// 	}
// 	printf("\n");

// }

// void ft_print_arrint(int *arr, char *name)
// {
// 	int i;
// 	int len;
// 	i = 0;
// 	len = sizeof(arr) / sizeof(int);
// 	printf("len%ld\n", sizeof(*arr));
// 	printf("printing array int %s\n{\n", name);
// 	while (i != len)
// 	{
// 		printf("\t %s[%d] = %d\n" , name, i, arr[5]);
// 		i++;
// 	}
// 	printf("{\n");
<<<<<<< HEAD
// }
=======
// }
>>>>>>> f7b171b00af0be478efea994be4b728396b12cfb
