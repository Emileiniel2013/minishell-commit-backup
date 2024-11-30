/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:24:36 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/07 17:51:38 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

void	handle_echo(t_mini *minish)
{
	t_cmd	*cpy;
	bool	nl;

	nl = true;
	cpy = minish->table->command;
	if (cpy->next == NULL)
		printf("\n");
	else
	{
		if (check_nl(cpy->next->content))
		{
			nl = false;
			cpy = cpy->next;
		}
		cpy = cpy->next;
		while (cpy != NULL)
		{
			write(minish->redirfd, cpy->content, ft_strlen(cpy->content));
			cpy = cpy->next;
			if (cpy != NULL)
				write(minish->redirfd, " ", 1);
		}
		if (nl == true)
			write(minish->redirfd, "\n", 1);
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
				write(minish->redirfd, &line[i++], 1);
			write (minish->redirfd, "\n", 1);
			free(line);
			return ;
		}
		i++;
	}
	line = malloc(PATH_MAX);
	getcwd(line, PATH_MAX);
	write (minish->redirfd, line, ft_strlen(line));
	write(minish->redirfd, "\n", 1);
	ft_free(&line);
}

void	handle_cd(t_mini *minish)
{
	char	*path;
	char	cwd[1024];

	path = NULL;
	if (minish->table->command->next)
		path = minish->table->command->next->content;
	getcwd(cwd, sizeof(cwd));
	if (!path || ((ft_strncmp(path, "~", 1) == 0)))
	{
		if (handle_cd_home(minish, path) != 0)
			return ;
	}
	else if ((ft_strncmp(path, "-", 1) == 0) && (ft_strlen(path) == 1))
	{
		if (handle_cd_oldpwd(minish) != 0)
			return ;
	}
	else
	{
		if (chdir(path) != 0)
			return (write_err(minish, 5, path));
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
		write(minish->redirfd, minish->env[i], ft_strlen(minish->env[i]));
		write(minish->redirfd, "\n", 1);
		i++;
	}
}

void	handle_export(t_mini *minish)
{
	char	*newvar;

	newvar = NULL;
	minish->table->command = minish->table->command->next;
	if (!minish->table->command)
		return (handle_env(minish));
	if (ft_strchr(minish->table->command->content, '=') == NULL)
		newvar = ft_check_var_lst(minish, minish->table->command->content);
	else
		newvar = ft_strdup(minish->table->command->content);
	if (newvar)
	{
		if (check_existing_var(newvar, minish) == -1)
			add_new_var_to_arr(newvar, minish);
		ft_free(&newvar);
	}
	if (minish->table->command->next != NULL)
		handle_export(minish);
}
