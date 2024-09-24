/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:37 by tndreka           #+#    #+#             */
/*   Updated: 2024/09/24 21:09:12 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//INCLUDES

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 	0
# define EXIT_FAILURE 	1

// STRUCT's
/* === comand === */
/* contains info of the comand
*/
typedef struct s_cmd
{
	char			*cmd;	
	int				flag;
	struct s_cmd	*next;
			
}	t_cmd;

/* === Command List === */
/*
* command table  which store every comand 
*/
typedef struct s_cmdlist
{
	t_cmd				*cmd;
	struct s_cmdlist	*next;
}	t_cmdlist;



/* === MINISHELL STRUCT ===*/
/*
*** This struct is going to contain every information if minishell data
*** comand info , comand table
*** input information.
*/
typedef struct s_msh
{
	char **env;
}	t_msh;


void prompt(t_msh *msh);


char **create_env(char **envp);
void free_env(t_msh *msh);

#endif