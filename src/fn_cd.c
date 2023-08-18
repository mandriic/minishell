#include "../inc/minishell.h"

char	**ft_copy_enviroment_vars_into_matrix2(char *envp_original[])
{
	int		i;
	int		num_vars;
	char	**matrix;

	i = 0;
	num_vars = -1;
	while (envp_original[++num_vars]);
	matrix = malloc(sizeof(char *) * (num_vars + 1));//puede no ser necesario
	while (envp_original[i])
	{
		matrix[i] = ft_strdup(envp_original[i]);
		i++;
	}
	matrix[i] = NULL;
	//esto hay que liberarlo
	return (matrix);
}

void ft_chdir(t_vars *vars)
{
    int cd_err;
    char **cb;
    char *pwd_loc;
    char **temp_old;
    char **temp_pwd;
    char **env_copy;
    static int first = 0;

    cd_err = -100;
    cb = vars->cmd_list->cmd;
    env_copy = vars->env_var;
    // env_copy = ft_copy_enviroment_vars_into_matrix2(vars->env_var);
    if(!cb[1])
    {
            // char *get_home;
            // get_home = getenv("HOME");
            cd_err = chdir(getenv("HOME"));

    }
    else
    {
        // printf("chCD\n");
        cd_err = chdir(cb[1]);
        if (cd_err == -1)
        {
            printf("cd: string not in pwd: %s\n", cb[1]);
        }
    }
    pwd_loc = getcwd(NULL, 0);
    // printf("pwd_loc %s\n", pwd_loc);
    vars->i = -1;
    while(env_copy[++vars->i])
    {
        if(!ft_strncmp(env_copy[vars->i], "OLDPWD", 6))
        {
            // printf("OLD -> %s\n", env_copy[vars->i]);
            temp_old = &env_copy[vars->i];            
        }
        if(!ft_strncmp(env_copy[vars->i], "PWD", 3))
        {
            // printf("PWD -> %s\n", env_copy[vars->i]);
            temp_pwd = &env_copy[vars->i];
        }
    }
    // ft_print_dp(env_copy, "111111111111");
    // printf("temp old 1 %p, %s \n", *temp_old, *temp_old);
    if (first++ != 0)
        free(*temp_old);
    // printf("temp old 2 %p, \n", *temp_old);
    *temp_old = ft_strjoin("OLD", *temp_pwd);
    // printf("temp old 3 %p, %s\n", *temp_old, *temp_old);
    if (first++ != 1)
        free(*temp_pwd);
    *temp_pwd = ft_strjoin("PWD=", pwd_loc);
    // ft_print_dp(env_copy, "2222222222222");
    free(pwd_loc);
    // printf("oldpwd %s\n", vars->env_var[14]);
    // ft_print_dp(vars->env_var, "ENV");
        // system("pwd");
    // printf("ERROR CD %d\n", cd_err);
    
}