/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:16:12 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 18:00:33 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	append_remainder(char **expanded_string, char **content, int pos)
{
	char	*temp;

	temp = ft_strdup(*expanded_string);
	free(*expanded_string);
	*expanded_string = ft_strjoin(temp, (*content) + pos);
	free(temp);
	temp = NULL;
}

void	replace_varname_wtih_var(char **expanded_string, char **env)
{
	char	*temp;

	temp = ft_strdup(*expanded_string);
	free(*expanded_string);
	*expanded_string = ft_strjoin(temp, *env);
	free(temp);
	free(*env);
	*env = NULL;
	temp = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*ft_getenv(t_mini *mini, char *env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	var = NULL;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], env, len) == 0 && mini->env[i][len] == '=')
		{
			var = ft_strdup(mini->env[i] + (len + 1));
			return (var);
		}
	}
	return (var);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	cpy[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			cpy[j] = ft_strdup(envp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (cpy);
}
