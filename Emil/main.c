/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:50:07 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/29 12:41:34 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	*mini;
	char	*line;

	handle_signals();
	mini = init_mini_vars(argc, argv, envp);
	while (1)
	{
		line = readline("Minishell $ ");
		if (!line)
			break ;
		parse_input(line, mini);
		free(line);
		if (mini->table && handle_redirections(mini) != -1)
		{
			if (!mini->table->rightpipe && check_builtin(mini))
				executor(mini);
			else
				mini_main(mini);
		}
		restore_redirections(mini);
		if (mini->table_head)
			free_table(mini);
	}
	free_mini(mini, false);
	return (0);
}
