/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/28 20:26:21 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_echo(t_mini *mini)	
{
	t_cmd	*command_cpy;
	bool	nl;

	nl = true;
	command_cpy = mini->table->command;
	
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

void	handle_pwd(t_mini *mini)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (mini->env[i] != NULL)
	{
		if (ft_strnstr(mini->env[i], "PWD=", 4) != NULL)
		{
			line = ft_strdup(mini->env[i]);
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

void	handle_cd(t_mini *mini)
{
	char	*path;
	char	*temp;
	char	cwd[1024];
	int		i;

	path = NULL;
	temp = NULL;
	i = 0;
	if (mini->table->command->next)
		path = mini->table->command->next->content;
	getcwd(cwd, sizeof(cwd)); 
	if (!path || ((ft_strncmp(path, "~", 1) == 0) && (ft_strlen(path) == 1)))
	{
		path = ft_getenv(mini, "HOME");
		if (!path)
		{
			write(STDERR_FILENO, "mini: cd: HOME not set\n", 29);
			mini->exit_code = 1;
			mini->success = false;
			return ;
		}
		i = chdir(path);
		free(path);
		path = NULL;
	}
	else if ((ft_strncmp(path, "-", 1) == 0) && (ft_strlen(path) == 1))
	{
		path = ft_getenv(mini, "OLDPWD");
		if (!path)
		{
			write(STDERR_FILENO, "mini: cd: OLDPWD not set\n", 31);
			mini->exit_code = 21;
			mini->success = false;
			return ;
		}
		i = chdir(path);
		if (i != 0)
		{
			write(STDERR_FILENO, "mini: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			mini->exit_code = 2;
			mini->success = false;
			free(path);
			path = NULL;
			return ;
		}
		free(path);
		path = NULL;
	}
	else if ((ft_strncmp(path, "~", 1) == 0) && (ft_strlen(path) != 1))
	{
		temp =	ft_getenv(mini, "HOME");
		if (!temp)
		{
			write(STDERR_FILENO, "mini: cd: HOME not set\n", 29);
			mini->exit_code = 1;
			mini->success = false;
			return ;
		}
		path = ft_strjoin(temp, path + 1);
		free(temp);
		temp = NULL;
		i = chdir(path);
		if (i != 0)
		{
			write(STDERR_FILENO, "mini: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			mini->exit_code = 2;
			mini->success = false;
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
			write(STDERR_FILENO, "mini: cd: ", 15);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
			mini->exit_code = 2;
			mini->success = false;
			return ;
		}
	}
	replace_env(mini, cwd, "OLDPWD=");
	getcwd(cwd, sizeof(cwd));
	replace_env(mini, cwd, "PWD=");
}

void	handle_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i] != NULL)
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
}

void	handle_export(t_mini *mini)
{
	char	**newenv;
	int		i;
	char	*newvar;
	
	i = 0;
	newenv = NULL;
	newvar = NULL;
	mini->table->command = mini->table->command->next;
	if (!mini->table->command)
	{
		handle_env(mini);
		return;
	}
	if (ft_strchr(mini->table->command->content, '=') == NULL)
		newvar = ft_check_var_lst(mini, mini->table->command->content);
	else
		newvar = ft_strdup(mini->table->command->content);
	if (newvar)
	{
		i = check_existing_var(newvar, mini);
		if (i == -1)
		{
			while (mini->env[++i] != NULL)
				;
			newenv = malloc(sizeof(char *) * (i + 2));
			newenv[i + 1] = NULL;
			newenv[i] = ft_strdup(newvar);
			free(newvar);
			newvar = NULL;
			while (--i >= 0)
				newenv[i] = ft_strdup(mini->env[i]);
			swap_vars(newenv);
			free_arr(mini->env);
			mini->env = newenv;
		}
		else
		{
			free(newvar);
			newvar = NULL;
		}
	}
	if (mini->table->command->next != NULL)
		handle_export(mini);
}

void	handle_unset(t_mini *mini)
{
	int		i;
	char	*var;
	size_t	len;

	i = 0;
	mini->table->command = mini->table->command->next;
	var = mini->table->command->content;
	while (mini->env[i] != NULL)
		i++;
	while (--i >= 0)
	{
		len = ft_strlen(var);
		if (ft_strncmp(mini->env[i], var, len) == 0 && mini->env[i][len] == '=')
		{
			free(mini->env[i]);
			while (mini->env[i + 1])
			{
				mini->env[i] = mini->env[i + 1];
				i++;
			}
			mini->env[i] = NULL;	
			break;
		}
	}
	if (mini->table->command->next != NULL)
		handle_unset(mini);
}

void        handle_exit(t_mini *mini)
{
	int	i;
	t_cmd	*command_cpy;
	char		*exit_code;
	
	i = 0;
	command_cpy = mini->table->command;
	exit_code = NULL;
	while(command_cpy)
	{
		command_cpy = command_cpy->next;
		i++;
	}
	if (i > 2)
	{
		write(STDERR_FILENO, "mini: exit: too many arguments\n", 36);
		mini->exit_code = 17;
		mini->success = false;
		return ;
	}
	else if (i == 2)
	{
		if (ft_isnumber(mini->table->command->next->content))
		{
			mini->exit_code = ft_atoi(mini->table->command->next->content);
			free_mini(mini, false);
			exit(mini->exit_code);
		}
		else
		{
			exit_code = mini->table->command->next->content;
			write(STDERR_FILENO, "mini: exit: ", 17);
			write(STDERR_FILENO, exit_code, ft_strlen(exit_code));
			write(STDERR_FILENO, ": numeric argument required\n", 29);
			mini->exit_code = 18;
			mini->success = false;
			return ;
		}
	}
	free_mini(mini, false);
	exit(EXIT_SUCCESS);
}

void	execute_file(t_mini *mini)
{
	char	*path;
	char	*filename;
	char	**arg_arr;
	char	**env;

	arg_arr = NULL;
	env = NULL;
	filename = mini->table->command->content;
	path = ft_strjoin(ft_getcwd(mini), filename + 1);
	if (access(path, X_OK) == 0)
	{
		arg_arr = create_arg_lst(mini);
		env = mini->env;
		free_mini(mini, true);
		execve(path, arg_arr, env);
	}
	else
	{
		write(STDERR_FILENO, "mini: ", 11);
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		mini->exit_code = 3;
		mini->success = false;
	}
}

void	check_path(t_mini *mini)
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
	if (access(mini->table->command->content, X_OK) == 0)
	{
		path = ft_strdup(mini->table->command->content);
		paths = list2array(mini);
		env = mini->env;
		free_mini(mini, true);
		execve(path, paths, env);
	}
	else
	{
		path = ft_getenv(mini, "PATH");
		if (!path)
		{
			path = mini->table->command->content;
			write(STDERR_FILENO, "mini: ", 11);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": command not found\n", 21);
			mini->exit_code = 4;
			mini->success = false;
			return ;
		}
		paths = ft_split(path, ':');
		free(path);
		while (paths[i] != NULL)
		{
			temp = ft_strjoin(paths[i], "/");
			path = ft_strjoin(temp, mini->table->command->content);
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
			paths = list2array(mini);
			env = mini->env;
			free_mini(mini, true);
			execve(path, paths, env);	
		}
		else
		{
			free_arr(paths);
			path = mini->table->command->content;
			write(STDERR_FILENO, "mini: ", 11);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, ": command not found\n", 21);
			mini->exit_code = 5;
			mini->success = false;
		}
	}
}