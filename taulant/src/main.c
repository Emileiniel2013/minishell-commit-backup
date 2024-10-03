/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/09/30 14:04:58 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"
/*
***		Mini SHELL
*** 
***
*** to do  
***	
***		PROMP 
***		HISTORY
***		PWD
***		'' -> handle single quote
***		"" -> handle double qoute
***		rederections
***		pipes
***		enviroment variables
***		$ -> handle dollar sign
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

void    leaks(void)
{
    system("leaks Minishell");
}
int main(int ac, char *av[], char *envp[])
{
	t_msh msh;
 	(void)ac;
	(void)av;
	(void)envp;

	
	msh.env = create_env(envp);
	atexit(leaks);
	prompt(&msh);
	free_env(&msh);	
	return(0);
}
