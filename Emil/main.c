/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:50:07 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/21 18:17:55 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell			*minishell;
	char				*line;
	
	minishell = init_mini_vars(argc, argv, envp);
	while(1)
	{
		line = readline("Minishell $ ");
		if (line && line[0] != '\0')
		{
			add_history(line);
			parse_input(line, minishell);
			free(line);
			if (minishell->table)
			{
				if (handle_redirections(minishell) != -1)
				{
					if (!minishell->table->rightpipe && check_builtin(minishell))
						executor(minishell);
					else
						mini_main(minishell);
				} // ELSE DESTROY AND FREE EVERYTHING !!!
			}
			restore_redirections(minishell);
		}
	}
	return (0);
}
