/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:36:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/28 18:19:35 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

int	check_existing_env(t_mini *minish, bool *found_env, char *env)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (minish->env[i])
	{
		size = ft_strlen(minish->env[i]);
		if (ft_strnstr(minish->env[i], env, size) != NULL)
		{
			*found_env = true;
			return (i);
		}
		i++;
	}
	return (i);
}

int	check_existing_var(char *newvar, t_mini *minish)
{
	int		i;
	char	*env;
	bool	join;

	i = 0;
	env = NULL;
	join = false;
	while (newvar[i] && newvar[i] != '=')
		i++;
	env = check_append_mode(newvar, i, &join);
	if (srch_and_rplc_env(env, newvar, minish, join))
	{
		ft_free(&env);
		return (i);
	}
	ft_free(&env);
	return (-1);
}

char	*check_append_mode(char *newvar, int i, bool *join)
{
	char	*env;

	env = NULL;
	if (newvar[i - 1] == '+')
	{
		*join = true;
		env = ft_strndup(newvar, i - 1);
	}
	else
		env = ft_strndup(newvar, i);
	return (env);
}

char	**list2array(t_mini *minish)
{
	int		i;
	t_cmd	*cmd;
	char	**arg_arr;

	cmd = minish->table->command;
	arg_arr = NULL;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	arg_arr = malloc(sizeof(char *) * (i + 1));
	if (!arg_arr)
		return (NULL);
	arg_arr[i] = NULL;
	cmd = minish->table->command;
	i = -1;
	while (cmd != NULL)
	{
		arg_arr[++i] = ft_strdup(cmd->content);
		cmd = cmd->next;
	}
	return (arg_arr);
}

bool	check_nl(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '\0')
		return (false);
	while (content[i])
	{
		if (i == 0 && content[i] == '-')
			i++;
		else if (content[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}
