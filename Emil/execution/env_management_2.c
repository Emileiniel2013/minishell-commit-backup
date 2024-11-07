/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:05:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 17:08:19 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

bool	srch_and_rplc_env(char *env, char *newvar, t_mini *minish, bool join)
{
	char	*temp;
	char	*new_env;
	char	*path;
	int		i;

	i = 0;
	new_env = NULL;
	path = ft_getenv(minish, env);
	if (path)
	{
		temp = ft_strjoin(env, "=");
		new_env = ft_strjoin(temp, path);
		ft_free(&temp);
		ft_free(&path);
		while (ft_strncmp(new_env, minish->env[i], ft_strlen(new_env)) != 0)
			i++;
		free(minish->env[i]);
		if (join)
			minish->env[i] = append_var(newvar, new_env);
		else
			minish->env[i] = ft_strdup(newvar);
		ft_free(&new_env);
		return (true);
	}
	return (false);
}

void	handle_shlvl(t_mini *minish, char sign)
{
	char	*num;
	int		i;

	num = ft_getenv(minish, "SHLVL");
	i = 0;
	if (!num || !ft_isnumber(num))
	{
		replace_env(minish, "1", "SHLVL=");
		if (num)
			ft_free(&num);
		return ;
	}
	i = ft_atoi(num);
	if (sign == '+')
		i++;
	else if (sign == '-')
		i--;
	free(num);
	num = ft_itoa(i);
	replace_env(minish, num, "SHLVL=");
	ft_free(&num);
}

void	unset_var(t_mini *minish, int i)
{
	free(minish->env[i]);
	while (minish->env[i + 1])
	{
		minish->env[i] = minish->env[i + 1];
		i++;
	}
	minish->env[i] = NULL;
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

bool	ft_isnumber(char *content)
{
	while (*content)
	{
		if (*content >= '0' && *content <= '9')
			content++;
		else
			return (false);
	}
	return (true);
}
