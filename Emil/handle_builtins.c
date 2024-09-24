/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/24 16:00:41 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/executor.h"

void	handle_echo(t_command *command)
{
	t_command	*command_cpy;
	bool		nl;

	nl = true;
	command_cpy = command;
	if (command_cpy->token == TOKEN_ARGUMENT)
	{
		nl = false;
		command_cpy = command_cpy->next;
	}
	while (command_cpy != NULL)
	{
		printf("%s", command_cpy->content);
		command_cpy = command_cpy->next;
		if (command_cpy != NULL)
			printf(" ");
	}
	if (nl == true)
		printf("\n");
}

void	handle_pwd(t_minishell *minishell)
{
	char	*line;
	int		i;
	size_t	size;

	line = NULL;
	size = 0;
	i = 0;
	while (minishell->env[i] != NULL)
	{
		size = ft_strlen(minishell->env[i]);
		if (ft_strnstr(minishell->env[i], "PWD=/", size) != NULL)
		{
			line = malloc(sizeof(char) * size + 1);
			ft_strlcpy(line, minishell->env[i], size + 1);
			break;
		}
		i++;
	}
	i = 4;
	while (line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
	write (1, "\n", 1);
}

void	handle_cd(t_minishell *minishell)
{
	char	*path;
	char	cwd[1024];

	if (minishell->table->next == NULL)
	{
		path = malloc(sizeof(char) * 16);
		ft_strlcpy(path, "/Users/temil-da", 16);
	}
	else
		path = minishell->table->simple_command->next->content;
	if (chdir(path) != 0)
	{
		printf("Minishell: cd: %s: No such file or directory\n", path);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	replace_env(minishell, cwd);
}

void	handle_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->env[i] != NULL)
	{
		printf("%s\n", minishell->env[i]);
		i++;
	}
}

void	handle_export(t_minishell *minishell)
{
	char	**newenv;
	int		i;
	size_t	len;
	
	i = 0;
	newenv = NULL;
	while (minishell->env[i] != NULL)
		i++;
	newenv = malloc(sizeof(char *) * i + 1);
	newenv[i + 1] = NULL;
	len = ft_strlen(minishell->table->simple_command->next->content);
	newenv[i] = malloc(sizeof(char) * len + 1);
	ft_strlcpy(newenv[i], minishell->table->simple_command->next->content, len + 1);	
	while (--i >= 0)
	{
		len = ft_strlen(minishell->env[i]);
		newenv[i] = malloc(sizeof(char) * len + 1);
		ft_strlcpy(newenv[i], minishell->env[i], len + 1);
	}
	swap_vars(newenv);
	free_env(minishell);
	minishell->env = newenv;
}

void	handle_unset(t_minishell *minishell)
{
	int		i;
	char	*var;
	size_t	len;

	i = 0;
	var = minishell->table->simple_command->next->content;
	while (minishell->env[i] != NULL)
		i++;
	while (--i >= 0)
	{
		len = ft_strlen(var);
		if (ft_strncmp(minishell->env[i], var, len) == 0)
		{
			free(minishell->env[i]);
			while (minishell->env[i] != NULL)
			{
				minishell->env[i] = minishell->env[i + 1];
				i++;
			}
			minishell->env[i] = NULL;	
			break;
		}
	}
}

void	check_path(t_minishell *minishell)
{
	char	*path;
	bool	valid_cmd;
	char	**paths;
	int		i;

	i = 0;
	valid_cmd = false;	
	path = getenv("PATH");
	paths = ft_split(path, ':');
	path = NULL;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], minishell->table->simple_command->content);
		if (access(path, X_OK) == 0)
		{
			valid_cmd = true;
			break ;
		}
		i++;
	}
	if (valid_cmd == true)
	{
		free(paths);
		paths = list2array(minishell);
		execve(path, paths, minishell->env);	
	}
	else
		printf("Minishell: %s: command not found\n", minishell->table->simple_command->content);
}