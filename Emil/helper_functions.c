/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/25 16:43:27 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	replace_env(t_minishell *minishell, char *path)
{
	int		i;
	size_t	size;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		size = ft_strlen(minishell->env[i]);
		if (ft_strnstr(minishell->env[i], "PWD=/", size) != NULL)
			break;
		i++;
	}
	free(minishell->env[i]);
	minishell->env[i] = ft_strjoin("PWD=", path);
}

void	free_env(t_minishell *minishell)
{
	int i;

	i = 0;

	while (minishell->env[i] != NULL)
		i++;
	while (i >= 0)
	{
		if (minishell->env[i])
			free(minishell->env[i]);
		i--;
	}
	free(minishell->env);
}

void	swap_vars(char **newenv)
{
	char	*temp;
	int		i;

	i = 0;
	while (newenv[i] != NULL)
			i++;
	temp = newenv[i - 1];
	newenv[i - 1] = newenv[i - 2];
	newenv[i - 2] = temp;
}

char	**list2array(t_minishell *minishell)
{
	int			i;
	t_command	*cmd;
	char		**arg_arr;

	cmd = minishell->table->simple_command;
	arg_arr = NULL;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	arg_arr = malloc(sizeof(char *) * i + 1);
	arg_arr[i] = NULL;
	cmd = minishell->table->simple_command;
	i = -1;
	while (cmd != NULL)
	{
		arg_arr[++i] = cmd->content;
		cmd = cmd->next;
	}
	return (arg_arr);
}
