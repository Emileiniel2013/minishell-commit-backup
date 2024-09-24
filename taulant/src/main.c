/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/09/24 15:39:36 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"
/*
***		Mini SHELL
*** 
***
***
***
***
***
***
***
***
***
***
***
***
***
***
*/
//void init_shell(t_msh *msh, char *envp[]);
// void prompt(void);
// void prompt(void)
// {
// 	ft_putstr("Minishell$ ");
// }

// // void init_shell(t_msh *msh, char *envp[])
// // {
// // 	(void)msh;
// // 	(void)envp;
	
// // }
int main(int ac, char *av[], char *envp[])
{
	// t_msh *msh;
	char **copy_envp = NULL;
	(void)ac;
	(void)av;
	copy_env(*envp, *copy_envp);
	//init_shell(&msh, envp);
	int i = 0 ;
	if (!isatty(STDIN_FILENO))
		return(EXIT_FAILAURE);
	// while (1)
	// {
	// 	prompt();
	// }
	return 0;
}
