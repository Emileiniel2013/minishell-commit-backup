/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:15:29 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 18:13:49 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	ft_free(char **content)
{
	if (*content)
	{
		free(*content);
		*content = NULL;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
	arr = NULL;
}

void	free_minish(t_mini *minish, bool keep_env)
{
	if (minish->table_head)
		free_table(minish);
	if (minish->env && !keep_env)
		free_arr(minish->env);
	if (minish->var_lst)
		free_arr(minish->var_lst);
	if (minish->in_redir)
	{
		free(minish->in_redir);
		minish->in_redir = NULL;
	}
	if (minish->out_redir)
	{
		free(minish->out_redir);
		minish->out_redir = NULL;
	}
	free(minish);
	minish = NULL;
}

void	exit_minish(t_mini *minish)
{
	int	status;

	status = minish->exit_code;
	free_minish(minish, false);
	exit(status);
}
