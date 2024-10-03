/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/03 14:43:27 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_minishell	*init_mini_vars(char *envp[])
{
	t_minishell			*minishell;
	t_command_table		*table;
	char				**envp_cpy;
	
	minishell = malloc(sizeof(t_minishell));
	table = malloc(sizeof(t_command_table));
	envp_cpy = copy_env(envp);
	minishell->table = table;
	minishell->env = envp_cpy;
	minishell->table->leftpipe = false;
	minishell->table->rightpipe = false;
	minishell->table->builtin = false;
	minishell->var_lst = NULL;
	return (minishell);
}