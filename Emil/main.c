/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:50:07 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/02 17:51:13 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <includes/executor.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell			*minishell;
	command_table		*table;
	char				**envp_cpy;
	(void)argv;
	(void)argc;

	minishell = malloc(sizeof(t_minishell));
	table = malloc(sizeof(t_command));
	envp_cpy = copy_env(envp);
	minishell->table = table;
	minishell->env = envp_cpy;
	minishell->table->leftpipe = false;
	minishell->table->rightpipe = false;
	minishell->table->builtin = false;
	minishell->var_lst = NULL;

	if (!minishell->table->rightpipe && minishell->table->builtin)
		executor(minishell);
	else
		mini_main(minishell);
	return (0);
}