/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:03:28 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 16:39:43 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	add_new_var_to_arr(char *newvar, t_mini *minish)
{
	int		i;
	char	**newenv;

	i = -1;
	newenv = NULL;
	while (minish->env[++i] != NULL)
		;
	newenv = malloc(sizeof(char *) * (i + 2));
	newenv[i + 1] = NULL;
	newenv[i] = ft_strdup(newvar);
	while (--i >= 0)
		newenv[i] = ft_strdup(minish->env[i]);
	swap_vars(newenv);
	free_arr(minish->env);
	minish->env = newenv;
}

char	*ft_check_var_lst(t_mini *mini, char *var)
{
	int		i;
	size_t	len;
	char	*new_var;

	i = -1;
	new_var = NULL;
	len = ft_strlen(var);
	while (mini->var_lst && mini->var_lst[++i])
	{
		if (ft_strncmp(mini->var_lst[i], var, len) == 0 && \
			mini->var_lst[i][len] == '=')
		{
			new_var = ft_strdup(mini->var_lst[i]);
			free(mini->var_lst[i]);
			while (mini->var_lst[i + 1])
			{
				mini->var_lst[i] = mini->var_lst[i + 1];
				i++;
			}
			mini->var_lst[i] = NULL;
			return (new_var);
		}
	}
	return (new_var);
}

void	replace_env(t_mini *minish, char *path, char *env)
{
	int		i;
	bool	found_env;
	char	**newenv;

	found_env = false;
	newenv = NULL;
	i = check_existing_env(minish, &found_env, env);
	if (found_env)
	{
		free(minish->env[i]);
		minish->env[i] = ft_strjoin(env, path);
	}
	else
	{
		newenv = malloc(sizeof(char *) * (i + 2));
		newenv[i + 1] = NULL;
		newenv[i] = ft_strjoin(env, path);
		while (--i >= 0)
			newenv[i] = ft_strdup(minish->env[i]);
		swap_vars(newenv);
		free_arr(minish->env);
		minish->env = newenv;
	}
}

void	add_var_to_list(t_mini *minish)
{
	int		i;
	char	**var_lst;

	i = 0;
	if (!minish->var_lst)
	{
		var_lst = malloc(sizeof(char *) * 2);
		var_lst[0] = ft_strdup(minish->table->command->content);
		var_lst[1] = NULL;
		minish->var_lst = var_lst;
	}
	else
	{
		while (minish->var_lst[i])
			i++;
		var_lst = malloc(sizeof(char *) * (i + 2));
		var_lst[i + 1] = NULL;
		var_lst[i] = ft_strdup(minish->table->command->content);
		while (--i >= 0)
			var_lst[i] = ft_strdup(minish->var_lst[i]);
		free_arr(minish->var_lst);
		minish->var_lst = var_lst;
	}
}

char	*append_var(char *newvar, char *env)
{
	int		j;
	char	*new_env;

	j = 0;
	new_env = NULL;
	while (newvar[j] != '=')
		j++;
	new_env = ft_strjoin(env, newvar + j + 1);
	return (new_env);
}
