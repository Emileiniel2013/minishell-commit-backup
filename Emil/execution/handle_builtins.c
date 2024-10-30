/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/30 12:27:54 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_echo(t_mini *minish)	
{
	t_cmd	*command_cpy;
	bool	nl;

	nl = true;
	command_cpy = minish->table->command;
	
	if (command_cpy->next == NULL)
		printf("\n");
	else
	{
		if (check_nl(command_cpy->next->content))
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

void	handle_pwd(t_mini *minish)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (minish->env[i] != NULL)
	{
		if (ft_strnstr(minish->env[i], "PWD=", 4) != NULL)
		{
			line = ft_strdup(minish->env[i]);
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

void	handle_cd(t_mini *minish)
{
	char	*path;
	char	*temp;
	char	cwd[1024];
	int		i;

	path = NULL;
	temp = NULL;
	i = 0;
	if (minish->table->command->next)
		path = minish->table->command->next->content;
	getcwd(cwd, sizeof(cwd)); 
	if (!path || ((ft_strncmp(path, "~", 1) == 0) && (ft_strlen(path) == 1)))
	{
		path = ft_getenv(minish, "HOME");
		if (!path)
		{
			write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
			minish->exit_code = 1;
			minish->success = false;
			return ;
		}
		i = chdir(path);
		free(path);
		path = NULL;
	}
	else if ((ft_strncmp(path, "-", 1) == 0) && (ft_strlen(path) == 1))
	{
		path = ft_getenv(minish, "OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "Minishell: cd: OLDPWD not set\n", 31);
			minish->exit_code = 21;
			minish->success = false;
			return ;
		}
		i = chdir(path);
		if (i != 0)
		{
			write(STDERR_FILENO, "Minishell: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			minish->exit_code = 2;
			minish->success = false;
			free(path);
			path = NULL;
			return ;
		}
		free(path);
		path = NULL;
	}
	else if ((ft_strncmp(path, "~", 1) == 0) && (ft_strlen(path) != 1))
	{
		temp =	ft_getenv(minish, "HOME");
		if (!temp)
		{
			write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
			minish->exit_code = 1;
			minish->success = false;
			return ;
		}
		path = ft_strjoin(temp, path + 1);
		free(temp);
		temp = NULL;
		i = chdir(path);
		if (i != 0)
		{
			write(STDERR_FILENO, "Minishell: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			minish->exit_code = 2;
			minish->success = false;
			free(path);
			path = NULL;
			return ;
		}
		free(path);
		path = NULL;
	}
	else
	{
		i = chdir(path);
		if (i != 0)
		{
			write(STDERR_FILENO, "Minishell: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			minish->exit_code = 2;
			minish->success = false;
			return ;
		}
	}
	replace_env(minish, cwd, "OLDPWD=");
	getcwd(cwd, sizeof(cwd));
	replace_env(minish, cwd, "PWD=");
}

void	handle_env(t_mini *minish)
{
	int	i;

	i = 0;
	while (minish->env[i] != NULL)
	{
		printf("%s\n", minish->env[i]);
		i++;
	}
}

void	handle_export(t_mini *minish)
{
	char	**newenv;
	int		i;
	char	*newvar;
	
	i = 0;
	newenv = NULL;
	newvar = NULL;
	minish->table->command = minish->table->command->next;
	if (!minish->table->command)
	{
		handle_env(minish);
		return;
	}
	if (ft_strchr(minish->table->command->content, '=') == NULL)
		newvar = ft_check_var_lst(minish, minish->table->command->content);
	else
		newvar = ft_strdup(minish->table->command->content);
	if (newvar)
	{
		i = check_existing_var(newvar, minish);
		if (i == -1)
		{
			while (minish->env[++i] != NULL)
				;
			newenv = malloc(sizeof(char *) * (i + 2));
			newenv[i + 1] = NULL;
			newenv[i] = ft_strdup(newvar);
			free(newvar);
			newvar = NULL;
			while (--i >= 0)
				newenv[i] = ft_strdup(minish->env[i]);
			swap_vars(newenv);
			free_arr(minish->env);
			minish->env = newenv;
		}
		else
		{
			free(newvar);
			newvar = NULL;
		}
	}
	if (minish->table->command->next != NULL)
		handle_export(minish);
}

void	handle_unset(t_mini *minish)
{
	int		i;
	char	*var;
	size_t	len;

	i = 0;
	minish->table->command = minish->table->command->next;
	var = minish->table->command->content;
	while (minish->env[i] != NULL)
		i++;
	while (--i >= 0)
	{
		len = ft_strlen(var);
		if (ft_strncmp(minish->env[i], var, len) == 0 && minish->env[i][len] == '=')
		{
			free(minish->env[i]);
			while (minish->env[i + 1])
			{
				minish->env[i] = minish->env[i + 1];
				i++;
			}
			minish->env[i] = NULL;	
			break;
		}
	}
	if (minish->table->command->next != NULL)
		handle_unset(minish);
}

void        handle_exit(t_mini *minish)
{
	int	i;
	t_cmd	*command_cpy;
	char	*exit_code;
	
	i = 0;
	command_cpy = minish->table->command;
	exit_code = NULL;
	while(command_cpy)
	{
		command_cpy = command_cpy->next;
		i++;
	}
	if (i > 2)
	{
		write(STDERR_FILENO, "Minishell: exit: too many arguments\n", 36);
		minish->exit_code = 17;
		minish->success = false;
		return ;
	}
	else if (i == 2)
	{
		if (ft_isnumber(minish->table->command->next->content))
		{
			minish->exit_code = ft_atoi(minish->table->command->next->content);
			free_mini(minish, false);
			exit(minish->exit_code);
		}
		else
		{
			exit_code = minish->table->command->next->content;
			write(STDERR_FILENO, "Minishell: exit: ", 17);
			write(STDERR_FILENO, exit_code, ft_strlen(exit_code));
			write(STDERR_FILENO, ": numeric argument required\n", 29);
			minish->exit_code = 18;
			minish->success = false;
			return ;
		}
	}
	free_mini(minish, false);
	exit(EXIT_SUCCESS);
}

void	execute_file(t_mini *minish)
{
	char	*path;
	char	*filename;
	char	**arg_arr;
	char	**env;

	arg_arr = NULL;
	env = NULL;
	filename = minish->table->command->content;
	path = ft_strjoin(ft_getcwd(minish), filename + 1);
	if (access(path, X_OK) == 0)
	{
		arg_arr = create_arg_lst(minish);
		env = minish->env;
		free_mini(minish, true);
		execve(path, arg_arr, env);
	}
	else
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		minish->exit_code = 3;
		minish->success = false;
	}
}

void	check_path(t_mini *minish)
{
	char	*path;
	bool	valid_cmd;
	char	**paths;
	int		i;
	char	**env;
	char	*temp;

	i = 0;
	valid_cmd = false;
	env = NULL;
	temp = NULL;
	path = NULL;
	paths = NULL;
	if (access(minish->table->command->content, X_OK) == 0)
	{
		path = ft_strdup(minish->table->command->content);
		paths = list2array(minish);
		env = minish->env;
		free_mini(minish, true);
		execve(path, paths, env);
	}
	else
	{
		path = ft_getenv(minish, "PATH");
		if (!path)
		{
			path = minish->table->command->content;
			write(STDERR_FILENO, "Minishell: ", 11);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": command not found\n", 21);
			minish->exit_code = 4;
			minish->success = false;
			return ;
		}
		paths = ft_split(path, ':');
		free(path);
		while (paths[i] != NULL)
		{
			temp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(temp, minish->table->command->content);
			free(temp);
			temp = NULL;
			if (access(path, X_OK) == 0)
			{
				valid_cmd = true;
				break ;
			}
			free(path);
			i++;
		}
		if (valid_cmd == true)
		{
			free_arr(paths);
			paths = list2array(minish);
			env = minish->env;
			free_mini(minish, true);
			execve(path, paths, env);	
		}
		else
		{
			free_arr(paths);
			path = minish->table->command->content;
			write(STDERR_FILENO, "Minishell: ", 11);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": command not found\n", 21);
			minish->exit_code = 5;
			minish->success = false;
		}
	}
}