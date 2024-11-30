/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:04:18 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/30 21:10:05 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

char	*ft_getcwd(t_mini *mini)
{
	int		i;
	char	*cwd;

	i = -1;
	cwd = NULL;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD=", 4) == 0)
		{
			cwd = ft_strdup(mini->env[i] + 4);
			return (cwd);
		}
	}
	return (NULL);
}

int	handle_cd_home(t_mini *minish, char *path)
{
	char	*temp;
	char	*new_path;
	int		i;

	i = 0;
	new_path = NULL;
	temp = ft_getenv(minish, "HOME");
	if (!temp)
		return (write_err(minish, 1, NULL), -1);
	if (!path || (ft_strlen(path) == 1))
	{
		i = chdir(temp);
		if (i != 0)
			write_err(minish, 4, temp);
	}
	else
	{
		new_path = ft_strjoin(temp, path + 1);
		i = chdir(new_path);
		if (i != 0)
			write_err(minish, 4, new_path);
		ft_free(&new_path);
	}
	ft_free(&temp);
	return (i);
}

int	handle_cd_oldpwd(t_mini *minish)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	path = ft_getenv(minish, "OLDPWD");
	if (!path)
		return (write_err(minish, 21, NULL), -1);
	i = chdir(path);
	if (i != 0)
	{
		write_err(minish, 2, path);
		ft_free(&path);
		return (-1);
	}
	printf("%s\n", path);
	ft_free(&path);
	return (0);
}

char	*check_valid_cmd(char **paths, t_mini *minish)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	temp = NULL;
	path = NULL;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, minish->table->command->content);
		ft_free(&temp);
		if (access(path, X_OK) == 0)
			return (path);
		ft_free(&path);
		i++;
	}
	return (path);
}

int		check_dir(char *path, t_mini *minish)
{
	if (strcmp(path, "/") == 0)
	{
		write(STDERR_FILENO, "Minishell: /: is a directory\n", 30);
		minish->exit_code = 34;
		return (-1);
	}
	else if (strcmp(path, "..") == 0)
		return (write_err(minish, 35, path), -1);
	else if (strcmp(path, ".") == 0)
		return (write_err(minish, 36, path), -1);
	return (0);
}
