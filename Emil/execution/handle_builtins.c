/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/10/11 18:12:51 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_echo(t_minishell *minishell)  // echo only prints it's own arguments it does not process input from the pipe, but it can redirect it to other commands
{
	t_command	*command_cpy;
	bool		nl;

	nl = true;
	command_cpy = minishell->table->simple_command;
	
	if (command_cpy->next == NULL)
		printf("\n");
	else
	{
		if (ft_strncmp(command_cpy->content, "-n", ft_strlen(command_cpy->content)) == 0)
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
	size_t	size;

	line = NULL;
	size = 0;
	i = 0;
	while (minishell->env[i] != NULL)
	{
		size = ft_strlen(minishell->env[i]);
		if (ft_strnstr(minishell->env[i], "PWD=/", size) != NULL)
		{
			line = ft_strdup(minishell->env[i]);
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

	if (minishell->table->simple_command->next == NULL)
	{
		path = ft_getenv(minishell, "HOME");
		if (!path)
		{
			printf("Minishell: cd: HOME not set\n");
			return ;
		}
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
		free_env(minishell);
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
	char	**arg_arr;

	path = minishell->table->simple_command->content;
	path = ft_strjoin(ft_getcwd(minishell), path + 1);
	if (access(path, X_OK) == 0)
	{
		arg_arr = create_arg_lst(minishell);
		if (!arg_arr)
		{
			arg_arr = malloc(sizeof(char *) * 2);
			arg_arr[0] = ft_strdup(minishell->table->simple_command->content);
			arg_arr[1] = NULL;
		}
		execve(path, arg_arr, minishell->env);
	}
	else
		printf("Minishell: cd: %s: No such file or directory\n", path);
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
		free(paths);
		paths = list2array(minishell);
		execve(path, paths, minishell->env);	
	}
	else
		printf("Minishell: %s: command not found\n", minishell->table->simple_command->content);
}