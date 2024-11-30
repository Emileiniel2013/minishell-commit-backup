/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:07:04 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/30 21:12:55 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_unset(t_mini *minish)
{
	int		i;
	char	*var;
	size_t	len;
	char	**env;

	i = 0;
	env = minish->env;
	minish->table->command = minish->table->command->next;
	if (minish->table->command)
		var = minish->table->command->content;
	else
		return ;
	while (env[i] != NULL)
		i++;
	while (--i >= 0)
	{
		len = ft_strlen(var);
		if ((ft_strncmp(env[i], var, len) == 0) && (env[i][len] == '='))
		{
			unset_var(minish, i);
			break ;
		}
	}
	if (minish->table->command->next != NULL)
		handle_unset(minish);
}

void	handle_exit(t_mini *minish)
{
	int		i;
	t_cmd	*command_cpy;

	i = 0;
	command_cpy = minish->table->command;
	while (command_cpy)
	{
		command_cpy = command_cpy->next;
		i++;
	}
	if (i > 2)
		return (write_err(minish, 17, NULL));
	else if (i == 2)
	{
		if (ft_isnumber(minish->table->command->next->content))
		{
			i = ft_atoi(minish->table->command->next->content);
			free_minish(minish, false);
			exit(i);
		}
		return (write_err(minish, 18, minish->table->command->next->content));
	}
	free_minish(minish, false);
	exit(EXIT_SUCCESS);
}

void	check_path(t_mini *minish)
{
	char	*path;
	char	**paths;

	path = ft_strdup(minish->table->command->content);
	paths = NULL;
	if (check_dir(path, minish) == -1)
		return (ft_free(&path));
	if (access(path, X_OK) == 0)
		execute_path(minish, path);
	else
	{
		ft_free(&path);
		path = ft_getenv(minish, "PATH");
		if (!path)
			return (write_err(minish, 24, minish->table->command->content));
		paths = ft_split(path, ':');
		ft_free(&path);
		path = check_valid_cmd(paths, minish);
		free_arr(paths);
		if (path)
			execute_path(minish, path);
		else
			write_err(minish, 23, minish->table->command->content);
	}
}

bool	check_builtin(t_mini *minish)
{
	char	*content;

	content = minish->table->command->content;
	if (minish->table != NULL)
	{
		if (ft_strcmp(content, "echo") == 0)
			return (true);
		else if (ft_strcmp(content, "pwd") == 0)
			return (true);
		else if (ft_strcmp(content, "cd") == 0)
			return (true);
		else if (ft_strcmp(content, "env") == 0)
			return (true);
		else if (ft_strcmp(content, "export") == 0)
			return (true);
		else if (ft_strcmp(content, "unset") == 0)
			return (true);
		else if (ft_strcmp(content, "exit") == 0)
			return (true);
		else if (ft_strchr(content + 1, '=') != NULL)
			return (true);
		else
			return (false);
	}
	return (false);
}

void	execute_path(t_mini *minish, char *path)
{
	char	**paths;
	char	**env;

	env = minish->env;
	paths = list2array(minish);
	free_minish(minish, true);
	execve(path, paths, env);
}
