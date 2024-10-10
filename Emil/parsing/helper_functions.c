/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/08 13:02:24 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*check_quoted_string(char **content, t_minishell *minishell)
{
	int		i;
	int		j;
	char	*expanded_env;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	expanded_env = NULL;
	while((*content)[i] && (*content)[i] != '$')
		i++;
	if (!(*content)[i])
		return (NULL);
	expanded_env = ft_strndup(*content, i);
	i++;
	while ((*content)[i] && (ft_isalnum((*content)[i]) == 1 || (*content)[i] == '_'))
	{
		i++;
		j++;
	}
	temp = ft_strndup((*content) + (i - j), j);
	temp = ft_getenv(minishell, temp);
	if (temp)
		expanded_env = ft_strjoin(expanded_env, temp);
	if ((*content)[i])
		expanded_env = ft_strjoin(expanded_env, (*content) + i);
	return (expanded_env);
}

char	*ft_getenv(t_minishell *minishell, char	*env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	while(minishell->env[++i])
	{
		if(ft_strncmp(minishell->env[i], env, len) == 0 && minishell->env[i][len] == '=')
		{
			var = ft_strdup(minishell->env[i] + len + 1);
			return (var);
		}
	}
	return (NULL);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	cpy[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		size = ft_strlen(envp[i]);
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (cpy);
}


void	expand_env_vars(char **content, t_minishell *minishell, token_type token)
{
	char	*expanded_env;

	expanded_env = NULL;
	if (token == TOKEN_STRING)
	{
		if ((*content)[0] == '$')
		{
			expanded_env = ft_getenv(minishell, *content + 1);
			if (expanded_env == NULL)
			{
				free(*content);
				*content = ft_strdup("");
			}
			else
			{
				free(*content);
				*content = ft_strdup(expanded_env);
				free(expanded_env);
			}
		}
	}
	else
	{
		while (1)
		{
			expanded_env = check_quoted_string(content, minishell);
			if (!expanded_env)
				break ;
			else
			{
				free(*content);
				(*content) = expanded_env;
			}
		}
	}
}
