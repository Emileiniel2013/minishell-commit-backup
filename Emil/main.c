/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:50:07 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/05 15:43:26 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell			*minishell;
	char				*line;
	(void)argv;
	(void)argc;


	minishell = init_mini_vars(envp);
	while(1)
	{
		line = readline("Minishell $ ");
		if (line && line[0] != '\0')
		{
			add_history(line);
			process_input(line);
		}
	}
	// if (!minishell->table->rightpipe && minishell->table->builtin)
	// 	executor(minishell);
	// else
	// 	mini_main(minishell);
	// return (0);
}