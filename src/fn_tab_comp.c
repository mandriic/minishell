/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_tab_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: preina-g <preina-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:59:47 by preina-g          #+#    #+#             */
/*   Updated: 2023/08/28 12:59:50 by preina-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"
//
//char **character_name_completion(const char *, int, int);
//char *character_name_generator(const char *, int);
//
//// char *character_names[] = {
////     "Arthur Dent",
////     "Ford Prefect",
////     "Tricia McMillan",
////     "Zaphod Beeblebrox",
////     NULL
//// };
//char **character_names;
//void ft_get_path_val(t_vars *vars)
//{
//	
//}
//character_names = ft_pars_path(ft_get_val("PATH", 
//vars->env_var), temp_cmd->cmd[0], 5, vars);
//
//char	**character_name_completion\
//(const char *text, int start, int end)
//{
//	rl_attempted_completion_over = 1;
//	return (rl_completion_matches(text, character_name_generator));
//}
//
//char *character_name_generator\
//(const char *text, int state)
//{
//	static int	list_index, len;
//	char		*name;
//
//	if (!state)
//	{
//		list_index = 0;
//		len = strlen(text);
//	}
//	name = character_names[list_index];
//	while (name != NULL) {
//		if (strncmp(name, text, len) == 0) {
//			return strdup(name);
//		}
//		name = character_names[++list_index];
//	}
//	return NULL;
//}