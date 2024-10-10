/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:50:07 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/08 10:59:53 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell			*minishell;
	char				*line;
	char				**envp_cpy;
	
	(void)argv;
	(void)argc;
	minishell = malloc(sizeof(t_minishell));
	envp_cpy = copy_env(envp);
	minishell->env = envp_cpy;
	minishell->var_lst = NULL;
	minishell->table = NULL;
	while(1)
	{
		line = readline("Minishell $ ");
		if (line && line[0] != '\0')
		{
			add_history(line);
			parse_input(line, minishell);
		}
	}
	// if (!minishell->table->rightpipe && minishell->table->builtin)
	// 	executor(minishell);
	// else
	// 	mini_main(minishell);
	// return (0);
}
