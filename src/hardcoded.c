#include "../inc/minishell.h"

void	dar_datos_a_los_cmd(t_command **cmd1, t_command **cmd2, t_command **cmd3)
{
	*cmd1 = malloc(sizeof(t_command));
	*cmd2 = malloc(sizeof(t_command));
	*cmd3 = malloc(sizeof(t_command));
	// *cmd4 = malloc(sizeof(t_command));
	

	(*cmd1)->comando_a_pelo = ft_strdup("ls");
	(*cmd1)->comando_con_flags = ft_strdup("ls -la");
	(*cmd1)->comando_bonito = ft_split("ls -la", ' ');
	(*cmd1)->infiles = NULL;
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("nl");
	(*cmd2)->comando_con_flags = ft_strdup("nl");
	(*cmd2)->comando_bonito = ft_split("nl", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("wc");
	(*cmd3)->comando_con_flags = ft_strdup("wc -l");
	(*cmd3)->comando_bonito = ft_split("wc -l", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = ft_split("salida", ' ');
	(*cmd3)->next = NULL;
	(*cmd3)->prev = *cmd2;

/* 
	(*cmd1)->comando_a_pelo = ft_strdup("cat");
	(*cmd1)->comando_con_flags = ft_strdup("cat");
	(*cmd1)->comando_bonito = ft_split("cat", ' ');
	(*cmd1)->infiles = ft_split("lotr.txt", ' ');
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("grep");
	(*cmd2)->comando_con_flags = ft_strdup("grep Moria");
	(*cmd2)->comando_bonito = ft_split("grep Moria", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("grep");
	(*cmd3)->comando_con_flags = ft_strdup("grep -n mines");
	(*cmd3)->comando_bonito = ft_split("grep -n mines", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = *cmd4;
	(*cmd3)->prev = *cmd2;

	(*cmd4)->comando_a_pelo = ft_strdup("nl");
	(*cmd4)->comando_con_flags = ft_strdup("nl");
	(*cmd4)->comando_bonito = ft_split("nl", ' ');
	(*cmd4)->infiles = NULL;
	(*cmd4)->outfiles = ft_split("wololo.txt", ' ');
	(*cmd4)->next = NULL;
	(*cmd4)->prev = *cmd3;
 */
/* 
	(*cmd1)->comando_a_pelo = ft_strdup("cat");
	(*cmd1)->comando_con_flags = ft_strdup("cat");
	(*cmd1)->comando_bonito = ft_split("cat", ' ');
	(*cmd1)->infiles = NULL;
	(*cmd1)->outfiles = NULL;
	(*cmd1)->next = *cmd2;
	(*cmd1)->prev = NULL;

	(*cmd2)->comando_a_pelo = ft_strdup("cat");
	(*cmd2)->comando_con_flags = ft_strdup("cat");
	(*cmd2)->comando_bonito = ft_split("cat", ' ');
	(*cmd2)->infiles = NULL;
	(*cmd2)->outfiles = NULL;
	(*cmd2)->next = *cmd3;
	(*cmd2)->prev = *cmd1;

	(*cmd3)->comando_a_pelo = ft_strdup("cat");
	(*cmd3)->comando_con_flags = ft_strdup("cat");
	(*cmd3)->comando_bonito = ft_split("cat", ' ');
	(*cmd3)->infiles = NULL;
	(*cmd3)->outfiles = NULL;
	(*cmd3)->next = *cmd4;
	(*cmd3)->prev = *cmd2;

	(*cmd4)->comando_a_pelo = ft_strdup("cat");
	(*cmd4)->comando_con_flags = ft_strdup("cat");
	(*cmd4)->comando_bonito = ft_split("cat", ' ');
	(*cmd4)->infiles = NULL;
	(*cmd4)->outfiles = NULL;
	(*cmd4)->next = NULL;
	(*cmd4)->prev = *cmd3;
 */
}
