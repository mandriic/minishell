#include "../inc/minishell.h"


int	main()
{
	ft_readline();
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
// }