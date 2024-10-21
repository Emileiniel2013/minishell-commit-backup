/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/21 15:51:20 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_echo(t_minishell *minishell)	
{
	t_command	*command_cpy;
	bool		nl;

	nl = true;
	command_cpy = minishell->table->simple_command;
	
	if (command_cpy->next == NULL)
		printf("\n");
	else
	{
		if (ft_strncmp(command_cpy->next->content, "-n", ft_strlen(command_cpy->next->content)) == 0)
		{
			nl = false;
			command_cpy = command_cpy->next;
		}
		command_cpy = command_cpy->next;
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
}

void	handle_pwd(t_minishell *minishell)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (minishell->env[i] != NULL)
	{
		if (ft_strnstr(minishell->env[i], "PWD=", 4) != NULL)
		{
			line = ft_strdup(minishell->env[i]);
			i = 4;
			while (line[i])
			{
				write(1, &line[i], 1);
				i++;
			}
			write (1, "\n", 1);
			free(line);
			return ;
		}
		i++;
	}
	line = malloc(PATH_MAX);
	getcwd(line, PATH_MAX);
	printf("%s\n", line);
	free(line);
}

void	handle_cd(t_minishell *minishell)
{
	char	*path;
	char	cwd[1024];

	if (minishell->table->simple_command->next == NULL)
	{
		path = ft_getenv(minishell, "HOME");
		if (!path)
		{
			write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
			return ;
		}
	}
	else
		path = minishell->table->simple_command->next->content;
	if (chdir(path) != 0)
	{
		write(STDERR_FILENO, "Minishell: cd: ", 15);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
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
	char	*newvar;
	
	i = 0;
	newenv = NULL;
	minishell->table->simple_command = minishell->table->simple_command->next;
	newvar = minishell->table->simple_command->content;
	if (ft_strchr(newvar, '=') == NULL)
		newvar = ft_check_var_lst(minishell, minishell->table->simple_command->content);
	if (newvar)
	{
		while (minishell->env[i] != NULL)
			i++;
		newenv = malloc(sizeof(char *) * (i + 2));
		newenv[i + 1] = NULL;
		newenv[i] = ft_strdup(newvar);
		while (--i >= 0)
			newenv[i] = ft_strdup(minishell->env[i]);
		swap_vars(newenv);
		free_arr(minishell->env);
		minishell->env = newenv;
	}
	if (minishell->table->simple_command->next != NULL)
		handle_export(minishell);
}

void	handle_unset(t_minishell *minishell)
{
	int		i;
	char	*var;
	size_t	len;

	i = 0;
	minishell->table->simple_command = minishell->table->simple_command->next;
	var = minishell->table->simple_command->content;
	while (minishell->env[i] != NULL)
		i++;
	while (--i >= 0)
	{
		len = ft_strlen(var);
		if (ft_strncmp(minishell->env[i], var, len) == 0 && minishell->env[i][len] == '=')
		{
			free(minishell->env[i]);
			while (minishell->env[i + 1])
			{
				minishell->env[i] = minishell->env[i + 1];
				i++;
			}
			minishell->env[i] = NULL;	
			break;
		}
	}
	if (minishell->table->simple_command->next != NULL)
		handle_unset(minishell);
}

void	execute_file(t_minishell *minishell)
{
	char	*path;
	char	*filename;
	char	**arg_arr;
	int		i;

	i = 0;
	arg_arr = NULL;
	filename = minishell->table->simple_command->content;
	path = ft_strjoin(ft_getcwd(minishell), filename + 1);
	if (access(path, X_OK) == 0)
	{
		arg_arr = create_arg_lst(minishell);
		execve(path, arg_arr, minishell->env);
	}
	else
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
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
	path = ft_getenv(minishell, "PATH");
	if (!path)
	{
		path = minishell->table->simple_command->content;
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": command not found\n", 21);
		return ;
	}
	paths = ft_split(path, ':');
	path = NULL;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, minishell->table->simple_command->content);
		if (access(path, X_OK) == 0)
		{
			valid_cmd = true;
			break ;
		}
		i++;
	}
	if (valid_cmd == true)
	{
		free_arr(paths);
		paths = list2array(minishell);
		execve(path, paths, minishell->env);	
	}
	else
	{
		free(path);
		free_arr(paths);
		path = minishell->table->simple_command->content;
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": command not found\n", 21);
	}	
}