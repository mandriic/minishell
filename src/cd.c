#include "../inc/minishell.h"

void    ft_cd(char *route)
{
    char    *directory;
    int     check;

    if (route == NULL)
    {
        check = chdir("~");
        printf("%d\n", check);
        directory = getcwd(NULL, 0);
        printf("%s\n", directory);
        free(directory);
    }
    else if (*route == '\0')
    {
        check = chdir("~");
        printf("%d\n", check);
        directory = getcwd(NULL, 0);
        printf("%s\n", directory);
        free(directory);
    }
    else
    {
        directory = getcwd(NULL, 0);
        printf("%s\n", directory);
        check = chdir(route);
        printf("%d\n", check);
        free(directory);
        directory = getcwd(NULL, 0);
        printf("%s\n", directory);
        free(directory);
    }
    


    return ;
}